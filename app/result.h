/* 
 * File:   result.h
 * Author: frederic
 *
 * Created on December 13, 2022, 7:03 AM
 */

#ifndef RESULT_H
#define	RESULT_H

#include <stdint.h>
#include "./programmer/prog_data.h"
#include "./app_data.h"

typedef enum {
    ERR_NONE = 0,
    ERR_BAD_COMMAND,
    ERR_BAD_INPUT_SIZE,
    ERR_FLASHER_ADDRESSES_EXPECTED,
    ERR_FLASHER_BAD_COMMAND,
    ERR_FLASHER_CONFIG_NOT_MATCH,
    ERR_INTERNAL,
} t_error_type;

typedef struct __attribute__((__packed__)) {
    uint8_t type;
    uint8_t size;
    char message[1];
} t_result_message;

typedef struct __attribute__((__packed__)) {
    uint8_t type;
    t_prog_row config;
} t_result_config;

typedef struct __attribute__((__packed__)) {
    uint8_t type;
    t_word words[21];
} t_result_words;

#define RESULT_BUF_SZ (USBGEN_EP_SIZE - (sizeof(t_result_message) - sizeof(((t_result_message *)0)->message)))
#define RESULT_TYPE_VALUE ((uint8_t)0xff)

#ifdef	__cplusplus
extern "C" {
#endif

uint8_t result_message_get_buffer_size(t_result_message *res);

#ifdef	__cplusplus
}
#endif

#endif	/* RESULT_H */
