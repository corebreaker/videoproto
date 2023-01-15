#include <xc.h>
#include <stdio.h>

#include "../mcc_generated_files/usb/usb.h"
#include "../mcc_generated_files/pin_manager.h"
#include "../delay.h"

#include "./flasher/flasher.h"
#include "./connect_state.h"
#include "./flasher.h"
#include "./result.h"
#include "./leds.h"

// App references
static t_ep_data *g_apps[] = {0};

// IO functions
static void read(t_ep_data *data) {
    uint16_t size = sizeof(data->buffer);

    memset(&data->buffer[0], 0, size);
    data->handle = USBRxOnePacket(data->ep, &data->buffer[0], size);
}

static void write(t_ep_data *data) {
    data->handle = USBTxOnePacket(data->ep, &data->buffer[0], data->size);
}

// Helper functions
static bool do_task(t_ep_data *data) {
    return CALLBACKS(data->callbacks)[data->cmd - 1](data);
}

static uint16_t get_len(t_ep_data *data) {
    data->size = sizeof(data->buffer);
    if (data->size > USBHandleGetLength(data->handle))
        data->size = USBHandleGetLength(data->handle);

    return data->size;
}

// Process functions
static void do_handshake(t_ep_data *data) {
    if (do_task(data)) {
        write(data);

        data->size = 0;
        data->state = 0;
        data->to_send = true;
    } else {
        read(data);
    }
}

static void manage_endpoint(t_ep_data *data) {
    if (USBHandleBusy(data->handle))
        return;

    if (data->to_send) {
        if (data->state && !do_task(data)) {
            write(data);

            return;
        }

        data->cmd = 0;
        data->size = 0;
        data->state = 0;
        data->to_send = false;

        read(data);

        return;
    }

    if (get_len(data)) {
        if (data->state) {
            do_handshake(data);

            return;
        }

        uint8_t code = data->buffer[0];

        if (!code) {
            led_signal_activate(LED_SIGNAL_ERROR, 2000);
            read(data);

            return;
        }

        led_signal_activate(LED_SIGNAL_PROG, 5000);

        uint8_t cmd = code - 1;

        if (cmd >= data->callback_count) {
            t_result_message *res = (t_result_message *)&data->buffer[0];

            res->type = ERR_BAD_COMMAND;
            res->size = (uint8_t)snprintf(&res->message[0], RESULT_BUF_SZ, "Bad command: %u", (unsigned)code);
            data->size = result_message_get_buffer_size(res);

            data->to_send = true;
            write(data);
            return;
        }

        data->cmd = code;
        do_handshake(data);
    }
}

static void do_app(t_ep_data *data) {
    if (!USBHandleBusy(data->handle)) {
        manage_endpoint(data);
    }
}

// Public functions
void init_app(void) {
    g_apps[0] = get_flasher_data();
}

void start_app(void) {
    USBEnableEndpoint(FLASHER_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    for (unsigned i = 0; i < (sizeof(g_apps) / sizeof(g_apps[0])); i++) {
        read(g_apps[i]);
    }
}

void app_loop(void) {
    if (!is_connected()) return;

    for (unsigned i = 0; i < (sizeof(g_apps) / sizeof(g_apps[0])); i++) {
        do_app(g_apps[i]);
    }
}
