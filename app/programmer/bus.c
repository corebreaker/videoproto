#include "../../mcc_generated_files/pin_manager.h"
#include "../../delay.h"
#include "./bus.h"

static void (*clk_delay)(void) = delay_prog_clk_standard;

static uint8_t recv_bit() {
    PRG_CLK_SetHigh();
    clk_delay(); 
    
    uint8_t res = (uint8_t)PRG_DAT_GetValue();
    
    PRG_CLK_SetLow();
    clk_delay();
    
    return res;
}

static void send_bit(uint8_t b) {
    if (!(b & 0x80)) {
        if (b & 1)
            PRG_DAT_SetHigh();
        else
            PRG_DAT_SetLow();
    }

    PRG_CLK_SetHigh();
    clk_delay(); 
    PRG_CLK_SetLow();
    clk_delay(); 
}

static void send_bit_zero_and_switch_to_read() {
    PRG_DAT_SetLow();
    PRG_CLK_SetHigh();
    clk_delay();
    PRG_CLK_SetLow();

    delay_prog_get_data();
    PRG_DAT_SetDigitalInput();
}

static void switch_to_write() {
    PRG_DAT_SetDigitalOutput();
}

void bus_init(void) {
    PRG_CLK_SetDigitalOutput();
    PRG_CLK_SetLow();

    PRG_DAT_SetDigitalOutput();
    PRG_DAT_SetLow();
}

void bus_uninit(void) {
    PRG_CLK_SetDigitalInput();
    PRG_DAT_SetDigitalInput();
}

void bus_reset(uint8_t dest) {
    bus_configure_dest(dest, 1);
    delay_ms(100);
    bus_configure_dest(dest, 0);
}

void set_clock_for_enhanced(bool enhanced) {
    clk_delay = enhanced ? delay_prog_clk_enhanced : delay_prog_clk_standard;
}

void send_key(uint32_t w) {
    for (uint32_t shift = 1UL << 31; shift; shift >>= 1) {
        send_bit((w & shift) ? (uint8_t)1 : (uint8_t)0);
    }
}

void send_word(uint32_t w, uint8_t bit_count) {
    for (; bit_count; bit_count--) {
        send_bit((uint8_t)(w & 1));
        w >>= 1;
    }
}

void send_command(uint32_t cmd) {
    send_word(cmd << 4, 28);
}

void send_nop(uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        send_word(0, 28);
    }
}

uint16_t bus_read_word() {
    send_word(1, 4);
    send_word(0, 7);
    send_bit_zero_and_switch_to_read();

    uint16_t res = 0;
    uint16_t mask = 1;

    for (uint8_t i = 0; i < 16; i++) {
        if (recv_bit())
            res |= mask;

        mask <<= 1;
    }

    switch_to_write();
    send_nop(1);

    return res;
}

void bus_configure_dest(uint8_t dest, uint8_t v) {
    if (dest & 1) {
        SDCARD_RESET_SetHigh();

        if (v & 1)
            SDCARD_RESET_SetDigitalInput();
        else {
            SDCARD_RESET_SetDigitalOutput();
            SDCARD_RESET_SetLow();
        }
    }

    if (dest & 2) {
        ALINX_RESET_SetHigh();

        if (v & 1)
            ALINX_RESET_SetDigitalInput();
        else {
            ALINX_RESET_SetDigitalOutput();
            ALINX_RESET_SetLow();
        }
    }

    if (dest & 4) {
        BBONE_RESET_SetHigh();

        if (v & 1)
            BBONE_RESET_SetDigitalInput();
        else {
            BBONE_RESET_SetDigitalOutput();
            BBONE_RESET_SetLow();
        }
    }
}
