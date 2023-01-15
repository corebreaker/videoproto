/* 
 * File:   logger.h
 * Author: frederic
 *
 * Created on January 7, 2023, 10:07 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <stdint.h>
#include <stdbool.h>

#define LED_STATUS_OFF 0
#define LED_STATUS_ON 1
#define LED_STATUS_TOGGLE 2

#define LED_LEFT 1
#define LED_RIGHT 2

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef void (*t_button_handler)(void);

#ifdef	__cplusplus
extern "C" {
#endif

void logger_init(void);
void logger_send_line(const char *content, uint8_t sz);
void logger_send_event(uint8_t eventId);
void logger_send_led_status(uint8_t led, uint8_t status);
void logger_on_push_button(t_button_handler handler);

#ifdef	__cplusplus
}
#endif

#endif	/* LOGGER_H */

