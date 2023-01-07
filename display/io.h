/* 
 * File:   screen_io.h
 * Author: frederic
 *
 * Created on January 4, 2023, 6:32 AM
 */

#ifndef DISPLAY_IO_H
#define	DISPLAY_IO_H

#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
void DisplayIO_PushByte(uint8_t v);

void DisplayIO_Reset(void);

void DisplayIO_PushPair(uint8_t hi, uint8_t lo);

void DisplayIO_BeginSend(bool data);
void DisplayIO_CommitSend(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SCREEN_IO_H */
