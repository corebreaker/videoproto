/* 
 * File:   data.h
 * Author: frederic
 *
 * Created on November 29, 2022, 8:01 PM
 */

#ifndef DATA_H
#define	DATA_H

#define BUFFER_SIZE 128

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    USB_HANDLE handle;
    bool to_send;
    uint16_t len;
} t_endpoint_data;

#endif	/* DATA_H */

