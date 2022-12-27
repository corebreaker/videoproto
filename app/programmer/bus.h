/* 
 * File:   bus.h
 * Author: frederic
 *
 * Created on December 4, 2022, 12:02 PM
 */

#ifndef BUS_H
#define	BUS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

void bus_init(void);
void bus_uninit(void);

void set_clock_for_enhanced(bool enhanced);

void send_key(uint32_t w);
void send_word(uint32_t w, uint8_t bit_count);

void send_nop(uint8_t count);
void send_command(uint32_t cmd);

void bus_reset(uint8_t dest);
void bus_configure_dest(uint8_t dest, uint8_t);

uint16_t bus_read_word(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BUS_H */

