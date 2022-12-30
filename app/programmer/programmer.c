#include "../../mcc_generated_files/pin_manager.h"
#include "../../delay.h"
#include "../leds.h"
#include "../app_data.h"
#include "./programmer.h"
#include "./bus.h"

void exit_reset_vector(void) {
    send_command(0x040200UL);
    send_nop(2);
}

void prog_enter(uint8_t dest, bool enhanced) {
    uint32_t code = 0x4D434850UL;

    bus_init();

    set_clock_for_enhanced(enhanced);
    if (!enhanced)
        code |= 1;

    bus_configure_dest(dest, 0);
    bus_configure_dest(dest, 1);
    delay_ms(15);

    send_key(code);
    delay_ms(2);

    bus_configure_dest(dest, 0);
    delay_ms(30);

    send_word(0, 9);
    send_word(0, 24);

    exit_reset_vector();
    
    led_prog(true);
}

void prog_exit(uint8_t dest) {
    bus_configure_dest(dest, 1);
    delay_ms(1);

    bus_uninit();
    
    led_prog(false);
}

bool prog_get_wr(void) {
    exit_reset_vector();

    send_command(0x803b05UL); // mov NVMCON (760), W5
    send_command(0x883c25UL); // mov W5, VISI (784)
    send_nop(2);

    uint16_t res = bus_read_word();

    send_nop(1);

    return (res & 0x8000) != 0;
}

uint32_t prog_read_word(uint32_t addr) {
    send_command(0x207847UL); // mov #VISI, W7
    send_nop(1);

    send_command(0x200000UL | ((addr >> 12) & 0xff0));
    send_command(0x8802a0UL); // mov W0, TBLPAG (054)
    send_nop(1);
    send_command(0x200006UL | ((addr << 4) & 0xffff0));
    send_nop(1);

    send_command(0xba0b96UL); // tblrdl [W6], [W7]
    send_nop(2);

    uint32_t res = (uint32_t)bus_read_word();

    send_nop(1);

    return res;
}

void prog_write_word(uint32_t addr, uint32_t val) {
    exit_reset_vector();

    send_command(0x24003aUL); // mov #0x4003, W10
    send_command(0x883b0aUL); // mov W10, NVMCON (760)
    send_nop(1);

    send_command(0x200000UL | ((addr >> 12) & 0xff0));
    send_command(0x8802a0UL); // mov W0, TBLPAG (054)
    send_nop(1);
    send_command(0x200007UL | ((addr << 4) & 0xffff0));
    send_nop(1);

    send_command(0x200000UL | ((val << 4) & 0xffff0));
    send_command(0x200001UL | ((val >> 12) & 0xff0));
    send_nop(1);

    send_command(0xeb0300UL); // clr W6
    send_nop(1);

    send_command(0xbb0bb6UL); // tblwtl [W6++], [W7]
    send_nop(2);

    send_command(0xbbcb96UL); // tblwth.b [W6], [W7]
    send_nop(2);

    send_command(0xa8e761UL); // bset NVMCON (760), #WR (15)
    send_nop(2);

    while (prog_get_wr());
}

void prog_erase(void) {
    exit_reset_vector();

    send_command(0x2404faUL); // mov #0x404f, W10
    send_command(0x883b0aUL); // mov W10, NVMCON (760))
    send_nop(1);

    send_command(0x200000UL); // mov #0, W0
    send_command(0x8802a0UL); // mov W0, TBLPAG (054)
    send_nop(1);

    send_command(0x200000UL); // mov #0, W0
    send_command(0xbb0800UL); // tblwtl W0, [W0]
    send_nop(2);

    send_command(0xa8e761UL); // bset NVMCON (760), #WR (15)
    send_nop(2);

    while (prog_get_wr());
}

static void inc_addr(uint16_t *addr) {
    *addr += 2;
    if (!(*addr & 0xffff)) {
        send_command(0xbad3d6UL); // inc.b TBLPAG
    }
}

void prog_read_block(t_prog_block *block) {
    uint16_t addr = block->addr;

    send_command(0x207847UL); // mov #VISI, W7
    send_nop(1);

    send_command(0x200000UL | ((addr >> 12) & 0xff0));
    send_command(0x8802a0UL); // mov W0, TBLPAG (054)
    send_nop(1);
    send_command(0x200006UL | ((addr << 4) & 0xffff0));
    send_nop(1);

    uint8_t size = sizeof(block->rows) / sizeof(block->rows[0]);
    bool is_partial = block->size && (block->size < size);

    if (is_partial) {
        size = block->size >> 2;
    }

    for (uint8_t i = 0; i < size; i++) {
        t_prog_row *row = &block->rows[i];

        exit_reset_vector();

        send_command(0xba0b96UL); // tblrdl [W6], [W7]
        send_nop(2);

        row->w1 = bus_read_word();

        send_command(0xbadbb6UL); // tblrdh.b [W6++], [W7++]
        send_nop(2);

        inc_addr(&addr);
        inc_addr(&addr);

        send_command(0xbad3d6UL); // tblrdh.b [++W6], [W7--]
        send_nop(2);

        uint16_t v = (uint16_t)bus_read_word();

        row->w1 |= (uint8_t)(v & 0xff);

        send_command(0xba0b96UL); // tblrdl [W6++], [W7]
        send_nop(2);

        row->w2 = bus_read_word() | (v << 4);

        inc_addr(&addr);
    }
    
    if (is_partial) {
        uint32_t *w = &block->rows[size].w1;

        size = block->size & 3;
        for (uint8_t i = 0; i < size; i++) {
            w[i] = prog_read_word(addr);
            addr += 2;
        }
    }
}

void prog_write_block(t_prog_block *block) {
    exit_reset_vector();

    send_command(0x24001aUL); // mov #0x4001, W10
    send_command(0x883b0aUL); // mov W10, NVMCON (760)
    send_nop(1);

    send_command(0x200000UL | ((block->addr >> 12) & 0xff0));
    send_command(0x8802a0UL); // mov W0, TBLPAG (054)
    send_nop(1);
    send_command(0x200007UL | ((block->addr << 4) & 0xffff0));
    send_nop(1);

    for (uint8_t i = 0; i < (sizeof(block->rows) / sizeof(block->rows[0])); i++) {
        t_prog_row *row = &block->rows[i];

        send_command(0x200000UL | ((row->w1 << 4) & 0xffff0));
        send_command(0x200001UL | ((row->w1 >> 12) & 0xff0) | ((row->w2 >> 4) & 0xff000));
        send_command(0x200002UL | ((row->w2 << 4) & 0xffff0));
        send_command(0x200003UL | ((row->w3 << 4) & 0xffff0));
        send_command(0x200004UL | ((row->w3 >> 12) & 0xff0) | ((row->w4 >> 4) & 0xff000));
        send_command(0x200005UL | ((row->w4 << 4) & 0xffff0));

        send_command(0xeb0300UL); // clr W6
        send_nop(1);

        send_command(0xbb0bb6UL); // tblwtl [W6++], [W7]
        send_nop(2);

        send_command(0xbbdbb6UL); // tblwth.b [W6++], [W7++]
        send_nop(2);

        send_command(0xbbebb6UL); // tblwth.b [W6++], [++W7]
        send_nop(2);

        send_command(0xbb1bb6UL); // tblwthl [W6++], [W7++]
        send_nop(2);

        send_command(0xbb0bb6UL); // tblwthl [W6++], [W7]
        send_nop(2);

        send_command(0xbbdbb6UL); // tblwth.b [W6++], [W7++]
        send_nop(2);

        send_command(0xbbebb6UL); // tblwth.b [W6++], [++W7]
        send_nop(2);

        send_command(0xbb1bb6UL); // tblwthl [W6++], [W7++]
        send_nop(2);
    }

    send_command(0xa8e761UL); // bset NVMCON (760), #WR (15)
    send_nop(2);

    while (prog_get_wr());
}

void prog_get_config(t_prog_row *config) {
    exit_reset_vector();

    uint32_t addr = 0x157fe;
    uint32_t *cw[4] = {
        &config->w1,
        &config->w2,
        &config->w3,
        &config->w4
    };

    send_command(0x207847UL); // mov #VISI (784), W7
    send_nop(1);

    send_command(0x200000UL | ((addr >> 12) & 0xff0));
    send_command(0x8802a0UL); // mov W0, TBLPAG (054)
    send_nop(1);
    send_command(0x200006UL | ((addr << 4) & 0xffff0));
    send_nop(1);

    for (uint8_t i = 0; i < 4; i++) {
        send_command(0xba0ba6UL); // tblrdl [W6--], [W7]
        send_nop(2);

        *cw[i] = (uint32_t)bus_read_word();
    }
}

void prog_set_config(t_prog_row *config) {
    exit_reset_vector();

    uint32_t addr = 0x157fe;
    uint32_t *cw[4] = {
        &config->w1,
        &config->w2,
        &config->w3,
        &config->w4
    };

    send_command(0x20000cUL | ((addr >> 12) & 0xff0));
    send_command(0x8802acUL); // mov W0, TBLPAG (054)
    send_nop(1);
    send_command(0x200007UL | ((addr << 4) & 0xffff0));
    send_nop(1);

    send_command(0x24003aUL); // mov #0x4003, W10
    send_command(0x883b0aUL); // mov W10, NVMCON
    send_nop(1);

    for (uint8_t i = 0; i < 4; i++) {
        send_command(0x200006UL | ((*cw[i] << 4) & 0xffff0));
        send_nop(1);

        send_command(0x200008UL); // mov #0, W8
        send_nop(1);

        send_command(0xbbcb88UL); // tblwth.b W8, [W7]
        send_nop(2);

        send_command(0xbb1386UL); // tblwtl.w W6, [W7--]
        send_nop(2);

        send_command(0xbb1386UL); // bset NVMCON (760), #WR (15)
        send_nop(2);

        while (prog_get_wr());
        
        exit_reset_vector();
    }
}
