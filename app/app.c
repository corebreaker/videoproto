#include <xc.h>
#include "../mcc_generated_files/usb/usb.h"
#include "../mcc_generated_files/pin_manager.h"
#include "../delay.h"
#include "./flasher/flasher.h"
#include "./connect_state.h"
#include "./flasher.h"

t_ep_data *g_apps[1] = {0};

static uint16_t get_len(t_ep_data *data) {
    data->size = sizeof(data->buffer);
    if (data->size > USBHandleGetLength(data->handle))
        data->size = USBHandleGetLength(data->handle);

    return data->size;
}

static void read(t_ep_data *data) {
    uint16_t size = sizeof(data->buffer);

    memset(&data->buffer, 0, sizeof(data->buffer));
    data->handle = USBRxOnePacket(data->ep, &data->buffer[0], size);
    data->to_send = false;
}

static void write(t_ep_data *data) {
    if (!data) {
        read(data);
        return;
    }

    data->handle = USBTxOnePacket(data->ep, &data->buffer[0], data->size);
    data->to_send = true;
}

static void manage_endpoint(t_ep_data *data) {
    if (data->to_send) {
        read(data);
        return;
    }

    if (get_len(data)) {
        switch (data->buffer[0]) {
            case 0x01:
            {
                t_ep_data *d = NULL;

                if (flasher_cmd_header(data)) {
                    d = data;
                }

                write(d);
                return;
            }

            case 0x02:
            {
                t_ep_data *d = NULL;

                if (flasher_cmd_record(data)) {
                    d = data;
                }

                write(d);
                return;
            }
        }
    }
}

void init_app(void) {
    g_apps[0] = get_flasher_data();
}

void start_app(void) {
    USBEnableEndpoint(FLASHER_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    for (unsigned i = 0; i < (sizeof(g_apps) / sizeof(g_apps[0])); i++) {
        read(g_apps[i]);
    }
}

static void do_app(t_ep_data *data) {
    if (!USBHandleBusy(data->handle)) {
        manage_endpoint(data);
    }
}

void app_loop(void) {
    if (!is_connected()) return;

    for (unsigned i = 0; i < (sizeof(g_apps) / sizeof(g_apps[0])); i++) {
        do_app(g_apps[i]);
    }
}
