/* 
 * File:   flasher_data.h
 * Author: frederic
 *
 * Created on December 13, 2022, 8:21 PM
 */

#ifndef FLASHER_DATA_H
#define	FLASHER_DATA_H

#include <stdint.h>
#include "../programmer/programmer.h"
#include "../app_data.h"

typedef struct __attribute__((__packed__)) {
    uint32_t address:23;
    uint32_t count:9;
} t_flasher_record_desc;

typedef struct __attribute__((__packed__)) {
    uint8_t cmd;
    uint8_t type;
    uint8_t _filler[2];
    t_flasher_record_desc addresses[15];
} t_flasher_cmd_addresses;

typedef struct __attribute__((__packed__)) {
    uint8_t cmd;
    t_word words[21];
} t_flasher_cmd_memory_record;

typedef struct __attribute__((__packed__)) {
    uint8_t cmd;
    uint8_t dest;
    uint8_t _filler[2];
    uint16_t address_count;
    uint16_t size;
    t_prog_row config;
    t_flasher_record_desc addresses[10];
} t_flasher_cmd_header;

typedef struct __attribute__((__packed__)) {
    uint8_t cmd;
    uint8_t dest;
    uint16_t count;
    uint32_t address;
} t_flasher_cmd_read_program;

typedef struct __attribute__((__packed__)) {
    uint8_t cmd;
    uint8_t dest;
} t_flasher_cmd_read_config;

#define RECORD_WORD_COUNT (sizeof(((t_flasher_cmd_memory_record *)0)->words) / sizeof(t_word))

#endif	/* FLASHER_DATA_H */

