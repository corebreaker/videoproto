#include "./mcc_generated_files/system.h"
#include "./delay.h"

#define FCY _XTAL_FREQ    // Instruction cycle frequency, Hz - required for __delayXXX() to work
#include <libpic30.h>        // __delayXXX() functions macros defined here

void delay_ms(uint16_t duration) {
    __delay_ms(duration);
}
