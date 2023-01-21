#include <string.h>
#include <stdbool.h>
#include "../mcc_generated_files/i2c1_driver.h"
#include "./logger.h"
#include "../app/leds.h"

static t_button_handler g_handler;

static uint8_t g_state = 0;

static uint8_t g_size = 0;
static uint8_t g_index = 0;
static uint8_t g_buffer[60] = {0};

static uint8_t g_event = 0;

static uint8_t g_led_status = 0;

static void writer() {
    switch (g_state) {
        // Message Len
        case 1:
            //I2C_Write(g_size);
            g_index = 0;
            g_state = 0;
            break;

        // Message Content
        case 2:
            if (g_index < g_size) {
                //I2C_Write(g_buffer[g_index++]);
            } else {
                g_size = 0;
                g_state = 0;
            }

            break;

        // Event
        case 3:
            if (g_event) {
                //I2C_Write(g_event);
                g_event = 0;
                led_signal_activate(LED_SIGNAL_READY, 0);
            }

            g_state = 0;
            break;

        // Led Status
        case 4:
            //I2C_Write(g_led_status);

            g_led_status = 0;
            g_state = 0;
            break;
    }
}

static void reader() {
    switch (0 /*I2C_Read()*/) {
        case 1:
            led_signal_activate(LED_SIGNAL_ERROR, 0);
            g_state = 1;
            break;
            
        case 2:
            led_signal_activate(LED_SIGNAL_ERROR, 0);
            g_state = 2;
            break;

        case 3:
            led_signal_activate(LED_SIGNAL_ERROR, 0);
            g_state = 3;
            break;

        case 4:
            led_signal_activate(LED_SIGNAL_ERROR, 0);
            g_state = 4;
            break;

        // Master button pushed
        case 8: {
            led_signal_activate(LED_SIGNAL_ERROR, 0);
            if (g_handler)
                g_handler();

            break;
        }
    }
}

void logger_init() {
    //I2C_SlaveSetReadIntHandler(reader);
    //I2C_SlaveSetWriteIntHandler(writer);
}

void logger_send_line(const char *content, uint8_t sz) {
    if (g_size)
        return;

    if (sz > 60)
        sz = 60;

    if (sz) {
        memmove(g_buffer, content, (size_t)sz);
        g_size = sz;
    }
}

void logger_send_event(uint8_t event_id) {
    if (g_event)
        return;

    //led_signal_activate(LED_SIGNAL_FLASH, 0);
    g_event = event_id;
}

void logger_send_led_status(uint8_t led, uint8_t status) {
    if (g_led_status)
        return;
    
    g_led_status = (uint8_t)(led << 2) | status;
}

void logger_on_push_button(t_button_handler handler) {
    g_handler = handler;
}
