/* 
 * File:   delay.h
 * Author: frederic
 *
 * Created on November 26, 2022, 4:58 PM
 */

#ifndef DELAY_H
#define	DELAY_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

void delay_ms(uint16_t);
void delay_us(uint32_t);

void delay_prog_clk_standard(void);
void delay_prog_clk_enhanced(void);
void delay_prog_get_data(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

