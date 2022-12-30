/* 
 * File:   prog_data.h
 * Author: frederic
 *
 * Created on 30 décembre 2022, 20:11
 */

#ifndef PROG_DATA_H
#define	PROG_DATA_H

#include <stdint.h>

typedef struct __attribute__((__packed__)) {
    uint32_t w1;
    uint32_t w2;
    uint32_t w3;
    uint32_t w4;
} t_prog_row;

typedef struct __attribute__((__packed__)) {
    uint32_t addr;
    uint8_t size;
    t_prog_row rows[16];
} t_prog_block;

#endif	/* PROG_DATA_H */

