#include <stdint.h>
#include "./connect_state.h"

static void null_handler(bool _) {}

static t_connection_state_handler g_handler = null_handler;
static uint8_t connection_state = 0;

void connection_signal_suspend(void) {
    connection_state |= 0x01;
    connection_state &= 0xF7;
}

void connection_signal_idle(void) {
    connection_state &= 0xFE;
    if (!(connection_state & 0x04)) {
        connection_state |= 0x08;
    }
}

void connection_signal_timer(void) {
    if (connection_state & 0x02) {
        connection_state |= 0x04;
        if (connection_state & 0x01) {
            connection_state &= 0xF8;
        }
    } else {
        connection_state &= 0xFB;
        if (connection_state & 0x01) {
            connection_state |= 0x02;
        }
    }
}

void set_connecion_state_handler(t_connection_state_handler handler) {
    g_handler = handler ? handler : null_handler;
}

void call_connect_state_handler(void) {
    if (connection_state & 0x08) {
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

bool is_connected(void) {
    return connection_state & 0x10;
}
