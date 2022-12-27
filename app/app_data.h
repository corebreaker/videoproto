/* 
 * File:   app_data.h
 * Author: frederic
 *
 * Created on November 29, 2022, 8:01 PM
 */

#ifndef APP_DATA_H
#define	APP_DATA_H

#include "../mcc_generated_files/usb/usb.h"

// Endpoint numbers
#define FLASHER_EP 1

// Config
#define BUFFER_SIZE 64

// Data structures
typedef union {
    uint8_t bytes[3];
    struct __attribute__((__packed__)) {
        uint16_t lsw;
        uint8_t msw;
    } parts;
} t_word;

typedef struct ep_data {
    uint8_t ep;
    USB_HANDLE handle;

    bool to_send;
    uint8_t state;
    uint8_t cmd;

    uint8_t callback_count;
    void *callbacks;

    uint16_t size;
    uint8_t buffer[BUFFER_SIZE];
} t_ep_data;

// Callbacks
typedef bool (*t_callback)(t_ep_data*);

#define CALLBACKS(c) ((t_callback *)c)

#ifdef	__cplusplus
extern "C" {
#endif

void make_bad_state_result(t_ep_data *data);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_DATA_H */

