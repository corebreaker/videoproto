/* 
 * File:   programmer.h
 * Author: frederic
 *
 * Created on 3 décembre 2022, 21:40
 */

#ifndef PROGRAMMER_H
#define	PROGRAMMER_H

#include <stdbool.h>
#include "./prog_data.h"

#ifdef	__cplusplus
extern "C" {
#endif

void prog_enter(uint8_t dest, bool enhanced);
void prog_exit(uint8_t dest);

void exit_reset_vector(void);

void prog_erase(void);

bool prog_get_wr(void);

uint32_t prog_read_word(uint32_t addr);
void prog_write_word(uint32_t addr, uint32_t val);

void prog_read_block(t_prog_block *block);
void prog_write_block(t_prog_block *block);

void prog_get_config(t_prog_row *config);
void prog_set_config(t_prog_row *config);

#ifdef	__cplusplus
}
#endif

#define PROG_BLOCK_WORD_COUNT (sizeof(((t_prog_block *)0)->rows) / sizeof(t_word))

#endif	/* PROGRAMMER_H */

