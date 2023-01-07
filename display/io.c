#include "../mcc_generated_files/pin_manager.h"
#include "../mcc_generated_files/spi1.h"
#include "../delay.h"

void DisplayIO_Reset(void) {
    EXT_ADDR1_SetHigh(); // CS
    EXT_ADDR0_SetLow(); // DC
    delay_us(10);

    EXT_ENABLE_SetLow(); // RST
    delay_ms(100);
    EXT_ENABLE_SetHigh(); // RST
    delay_ms(100);
}

void DisplayIO_PushPair(uint8_t hi, uint8_t lo) {
    SPI1_Exchange8bit(hi);
    SPI1_Exchange8bit(lo);
}

void DisplayIO_PushByte(uint8_t v) {
    SPI1_Exchange8bit(v);
}

void DisplayIO_BeginSend(bool data) {
    if (data) {
        EXT_ADDR0_SetHigh(); // DC
    } else {
        EXT_ADDR0_SetLow(); // DC
    }

    EXT_ADDR1_SetLow(); // CS
}

void DisplayIO_CommitSend(void) {
    EXT_ADDR1_SetHigh(); // CS    
}
