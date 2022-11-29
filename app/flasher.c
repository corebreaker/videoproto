#include <xc.h>
#include <stdio.h>
#include "string.h"
#include "../mcc_generated_files/usb/usb.h"
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

bool flasher_cmd_header(t_endpoint_data *data) {
    char buffer[64];
    t_flasher_cmd_header *header = (t_flasher_cmd_header *)&data->buffer[0];
    t_flasher_record_desc *d1 = (t_flasher_record_desc *)&header->addresses[0];
    t_flasher_record_desc *d2 = d1 + 1;

    buffer[0] = (uint8_t)snprintf(
            buffer,
            sizeof(buffer),
            "DEST:%02x, SIZE: %u, COUNT:%u; 1.ADDR=%06lu/SZ=%lu; 2.ADDR=%06lu/SZ=%lu",
            header->dest,
            data->len,
            header->count,
            (uint32_t)d1->address,
            (uint32_t)d1->size,
            (uint32_t)d2->address,
            (uint32_t)d2->size
        );

    data->len = (uint16_t)buffer[0];
    memmove(&data->buffer[0], buffer, buffer[0] + 1);

    return true;
}

bool flasher_cmd_record(t_endpoint_data *data) {
    return true;
}
