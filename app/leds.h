/* 
 * File:   leds.h
 * Author: frederic
 *
 * Created on 16 décembre 2022, 17:53
 */

#ifndef LEDS_H
#define	LEDS_H

#include <stdbool.h>

typedef enum {
    LED_SIGNAL_READY,
    LED_SIGNAL_ERROR,
    LED_SIGNAL_PROG,
    LED_SIGNAL_FLASH,
} t_led_signal_type;

#ifdef	__cplusplus
extern "C" {
#endif

void led_ready(bool on);
void led_error(bool on);

void led_prog(bool on);
void led_flash(bool on);

void led_signal_event();
void led_signal_activate(t_led_signal_type signal_type, uint32_t val);

#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */
