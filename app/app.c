#include <xc.h>
#include <stdio.h>
#include "../mcc_generated_files/usb/usb.h"
#include "./app.h"

#define FLASHER_EP _EP01_OUT

#define BUFFER_SIZE 64

static uint8_t flash_buffer[BUFFER_SIZE];
static USB_HANDLE flash_handle;
static bool to_send = false;

void init_app(void) {
    USBEnableEndpoint(FLASHER_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    flash_handle = USBRxOnePacket(FLASHER_EP, flash_buffer, sizeof(flash_buffer));
    to_send = false;
}

void app_loop(void) {
    if (to_send) {
        if (!USBHandleBusy(flash_buffer)) {
            flash_handle = USBRxOnePacket(FLASHER_EP, flash_buffer, sizeof(flash_buffer));
            to_send = false;
        }
    } else {
        if (!USBHandleBusy(flash_buffer)) {
            uint16_t len = sizeof(flash_buffer);

            if (len > USBHandleGetLength(flash_buffer))
                len = USBHandleGetLength(flash_buffer);

            if (len) {
                uint16_t value = (uint16_t)flash_buffer[0] | ((len > 1) ? ((uint16_t)flash_buffer[1]) << 8 : 0);

                flash_buffer[0] = (uint8_t)snprintf((char *)flash_buffer + 1, sizeof(flash_buffer) - 1, "Value: %u", value);

                flash_handle = USBTxOnePacket(FLASHER_EP, flash_buffer, len);
            }

            to_send = true;
        }
    }
}
