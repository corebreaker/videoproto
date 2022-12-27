#include <xc.h>
#include <stdio.h>

#include "./flasher/flasher.h"
#include "./result.h"
#include "./app.h"
#include "./leds.h"
#include "./connect_state.h"
#include "./app_data.h"
#include "../delay.h"

static uint8_t bb[64];

// IO functions
static void read(t_ep_data *data) {
    uint16_t size = sizeof(data->buffer);

    data->handle = USBRxOnePacket(data->ep, &/*data->buffer*/bb[0], size);
}

static void write(t_ep_data *data) {
    data->handle = USBTxOnePacket(data->ep, &/*data->buffer*/bb[0], data->size);
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

static void do_handshake(t_ep_data *data) {
    if (do_task(data)) {
        write(data);
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

        data->size = 0;
        data->cmd = 0;
        data->state = 0;
        data->to_send = false;
        memset(&/*data->buffer*/bb[0], 0, sizeof(data->buffer));

        read(data);

        return;
    }
    
    if (get_len(data)) {
        if (data->state) {
            do_handshake(data);

            return;
        }

        uint8_t code = /*data->buffer*/bb[0];

        if (!code) {
            led_signal_activate(LED_SIGNAL_ERROR, 2000);
            read(data);

            return;
        }

        led_signal_activate(LED_SIGNAL_PROG, 5000);

        uint8_t cmd = code - 1;

        if (cmd >= data->callback_count) {
            t_result_message *res = (t_result_message *)&/*data->buffer*/bb[0];

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

// App functions
void init_app(void) {
    USBEnableEndpoint(FLASHER_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    read(&flasher);
}

static void do_app(t_ep_data *data) {
    if (!USBHandleBusy(data->handle)) {
        memset(&/*data->buffer*/bb, 0, sizeof(data->buffer));
        manage_endpoint(data);
    }
}

void app_loop(void) {
    if (!is_connected()) return;

    do_app(&flasher);
}
