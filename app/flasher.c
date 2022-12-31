#include <xc.h>
#include <stdio.h>
#include "string.h"
#include "./flasher.h"

typedef struct {
    uint32_t size:8;
    uint32_t address:24;
} t_flasher_record_desc;

typedef struct {
    uint8_t cmd;
    uint8_t dest;
    uint16_t count;
    t_flasher_record_desc addresses[1];
} t_flasher_cmd_header;

static char buffer[127];
static uint16_t buf_size;

bool flasher_cmd_header(t_ep_data *data) {
    t_flasher_cmd_header *header = (t_flasher_cmd_header *)&data->buffer[0];
    t_flasher_record_desc *d1 = (t_flasher_record_desc *)&header->addresses[0];
    t_flasher_record_desc *d2 = d1 + 1;

    buf_size = (uint16_t)snprintf(
            buffer,
            sizeof(buffer),
            "DEST:%02x, SIZE: %u, COUNT:%u; 1.ADDR=%06lx/SZ=%lx; 2.ADDR=%06lx/SZ=%lx",
            header->dest,
            data->size,
            header->count,
            (uint32_t)d1->address,
            (uint32_t)d1->size,
            (uint32_t)d2->address,
            (uint32_t)d2->size
        );

    data->size = (buf_size < 64) ? (buf_size + 1) : 64;

    data->buffer[0] = (uint8_t)(data->size - 1);
    memmove(&data->buffer[1], buffer, data->size - 1);

    return true;
}

bool flasher_cmd_record(t_ep_data *data) {
    data->size = 1;
    if (buf_size > 63) {
        uint16_t size = buf_size - 63;

        data->buffer[0] = (uint8_t)size;

        data->size = size + 1;
        memmove(&data->buffer[1], &buffer[63], size);
    }

    data->buffer[0] = (uint8_t)(data->size - 1);

    return true;
}
