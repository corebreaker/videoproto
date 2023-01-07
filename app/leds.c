#include <stdbool.h>
#include "../mcc_generated_files/pin_manager.h"
#include "../delay.h"
#include "./leds.h"

void led_ready(bool on) {
    if (on) {
        LED_READY_SetHigh();
    } else {
        LED_READY_SetLow();
    }
}

void led_error(bool on) {
    if (on) {
        LED_ERROR_SetHigh();
    } else {
        LED_ERROR_SetLow();
    }
}

void led_prog(bool on) {
    if (on) {
        LED_PROG_SetHigh();
    } else {
        LED_PROG_SetLow();
    }
}

void led_flash(bool on) {
    if (on) {
        LED_FLASH_SetHigh();
    } else {
        LED_FLASH_SetLow();
    }
}

void led_right(bool on) {
    if (on) {
        EXT_D0_SetHigh();
    } else {
        EXT_D0_SetLow();
    }
}

void led_left(bool on) {
    if (on) {
        EXT_D1_SetHigh();
    } else {
        EXT_D1_SetLow();
    }
}

static uint32_t signal_state_ready = 0;
static uint32_t signal_state_error = 0;
static uint32_t signal_state_prog = 0;
static uint32_t signal_state_flash = 0;

void led_signal_event() {
    if (signal_state_ready && (!--signal_state_ready)) {
        LED_READY_SetLow();
    }

    if (signal_state_error && (!--signal_state_error)) {
        LED_ERROR_SetLow();
    }

    if (signal_state_prog && (!--signal_state_prog)) {
        LED_PROG_SetLow();
    }

    if (signal_state_flash && (!--signal_state_flash)) {
        LED_FLASH_SetLow();
    }
}

void led_signal_activate(t_led_signal_type signal_type, uint32_t val) {
    if (!val) val = 5000;

    switch (signal_type) {
        case LED_SIGNAL_READY:
            signal_state_ready = val;
            LED_READY_SetHigh();
            break;

        case LED_SIGNAL_ERROR:
            signal_state_error = val;
            LED_ERROR_SetHigh();
            break;

        case LED_SIGNAL_PROG:
            signal_state_prog = val;
            LED_PROG_SetHigh();
            break;

        case LED_SIGNAL_FLASH:
            signal_state_flash = val;
            LED_FLASH_SetHigh();
            break;
    }
}
