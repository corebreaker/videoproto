#include "./mcc_generated_files/system.h"
#include "./delay.h"

#define FCY _XTAL_FREQ    // Instruction cycle frequency, Hz - required for __delayXXX() to work
#include <libpic30.h>        // __delayXXX() functions macros defined here

void delay_ms(uint16_t duration) {
    __delay_ms(duration);
}

void delay_us(uint32_t duration) {
    if (duration < 1000000UL)
        __delay32( (unsigned long) ((FCY) / (1000000ULL / duration)));
    else
        __delay32( (unsigned long) ((duration / 1000000ULL) * (FCY)));
}

#define fixed_delay(div) __delay32((unsigned long)((FCY < div) ? 1UL : ((FCY) / div)))

void delay_prog_clk_standard() {
    // 50 ns per level => period of 100ns
    fixed_delay(10000000ULL);
}

void delay_prog_clk_enhanced() {
    // 125 ns per level => period of 250ns
    fixed_delay(8000000ULL);
}

void delay_prog_get_data() {
    // 20 ns
    fixed_delay(50000000ULL);
}
