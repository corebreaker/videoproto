#include <xc.h>
#include "../mcc_generated_files/usb/usb.h"
#include "../mcc_generated_files/pin_manager.h"
#include "../delay.h"
#include "./connect_state.h"
#include "./flasher.h"
#include "./app.h"

#define FLASHER_EP 1

static t_endpoint_data flasher;

static uint16_t get_len(t_endpoint_data *data) {
    data->len = sizeof(data->buffer);
    if (data->len > USBHandleGetLength(data->handle))
        data->len = USBHandleGetLength(data->handle);

    return data->len;
}

static void read(uint8_t ep, t_endpoint_data *data) {
    uint16_t size = sizeof(data->buffer);

    data->handle = USBRxOnePacket(ep, &data->buffer[0], size);
    data->to_send = false;
}

static void write(uint8_t ep, t_endpoint_data *data) {
    if (!data) {
        read(ep, data);
        return;
    }

    data->handle = USBTxOnePacket(ep, &data->buffer[0], data->len);
    data->to_send = true;
}

static void manage_endpoint_flasher() {
    if (flasher.to_send) {
        read(FLASHER_EP, &flasher);
        return;
    }

    if (get_len(&flasher)) {
        switch (flasher.buffer[0]) {
            case 0x01:
            {
                t_endpoint_data *data = NULL;

                if (flasher_cmd_header(&flasher)) {
                    data = &flasher;
                }

                write(FLASHER_EP, data);
                return;
            }

            case 0x02:
            {
                t_endpoint_data *data = NULL;
                
                if (flasher_cmd_record(&flasher)) {
                    data = &flasher;
                }

                write(FLASHER_EP, data);
                return;
            }
        }
    }
}

void init_app(void) {
    USBEnableEndpoint(FLASHER_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    read(FLASHER_EP, &flasher);
}

void app_loop(void) {
    if (!is_connected()) return;
    
    if (!USBHandleBusy(flasher.handle)) {
        manage_endpoint_flasher();
    }
}
