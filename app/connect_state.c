#include <stdint.h>
#include "./connect_state.h"

static void null_handler(bool _) {}

static t_connection_state_handler g_handler = null_handler;
static uint8_t connection_state = 0;

void connection_signal_usb_event(void) {
    connection_state &= 0xfe;
}

void connection_signal_usb_start(void) {
    connection_state |= 0x01;
}

void connection_signal_timer(void) {
    if (connection_state & 0x01) {
        if (!(connection_state & 0x10)) {
            g_handler(true);
            connection_state |= 0x10;
        }
    } else {
        if (connection_state & 0x10) {
            g_handler(false);
            connection_state &= 0xEF;
        }
    }
}

void set_connecion_state_handler(t_connection_state_handler handler) {
    g_handler = handler ? handler : null_handler;
}

bool is_connected(void) {
    return connection_state & 0x01;
}
