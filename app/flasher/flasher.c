#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../programmer/bus.h"
#include "../programmer/programmer.h"
#include "../result.h"
#include "../leds.h"
#include "./flasher.h"
#include "./flasher_data.h"

static uint8_t g_dest;
static bool g_enhanced;

static t_flasher_cmd_read_program g_read;
static t_flasher_cmd_header g_header;

static uint16_t g_desc_count = 0;                 // Count of descs read from USB by following the infos in the header
static uint16_t g_record_count = 0;               // Count of records
static t_flasher_record_desc *g_record_descs = 0; // List of desc read from the header

static uint16_t g_record_pos = 0;                 // Position of the read record sent through USB from program memory

static uint16_t g_desc_list_idx = 0;              // Position in the list of desc
static uint16_t g_current_desc_pos = 0;           // Position in the current desc got from the list of descs

static uint8_t g_block_pos = 0;                   // Position in the current block
static t_prog_block g_block = {0};                // Current block to flash

static bool flasher_cmd_record(t_ep_data *data) {
    t_flasher_cmd_memory_record *record = (t_flasher_cmd_memory_record *)&data->buffer[0];
    uint32_t *addresses = &g_block.rows[0].w1;
    uint8_t i;

    data->state = 2;

    for (i = 0; i < RECORD_WORD_COUNT; i++) {
        t_word *w = &record->words[i];

        g_current_desc_pos++;
        addresses[g_block_pos++] = ((uint32_t)(w->parts.msw) << 16) | ((uint32_t)(w->parts.lsw));
        if ((g_block_pos >= PROG_BLOCK_WORD_COUNT) || (g_current_desc_pos >= g_record_descs[g_desc_list_idx].count))
            break;
    }

    if (i < RECORD_WORD_COUNT) {
        t_flasher_record_desc *desc = g_record_descs + g_desc_list_idx;

        if (g_current_desc_pos < desc->count) {
            prog_write_block(&g_block);

            g_block_pos = 0;
            g_block.addr = desc->address;            
            
            return false;
        }

        
    }

    return false;
}

static void get_addresses(t_ep_data *data) {
    t_flasher_cmd_addresses *addresses = (t_flasher_cmd_addresses *)&data->buffer[0];

    if (addresses->type != 1) {
        t_result_message *res = (t_result_message *)&data->buffer[0];

        res->type = ERR_FLASHER_ADDRESSES_EXPECTED;
        res->size = (uint8_t)snprintf(
            &res->message[0],
            RESULT_BUF_SZ,
            "Flasher addresses expected: %u",
            (unsigned)addresses->type
        );

        data->size = result_message_get_buffer_size(res);

        return;
    }

    if (!g_record_descs) {
        t_result_message *res = (t_result_message *)&data->buffer[0];

        res->type = ERR_INTERNAL;
        res->size = (uint8_t)snprintf(&res->message[0], RESULT_BUF_SZ, "Flasher addresses are not allocated");

        data->size = result_message_get_buffer_size(res);

        return;
    }

    uint16_t remaining = g_header.address_count - g_desc_count;
    bool is_end = remaining <= (sizeof(addresses->addresses) / sizeof(addresses->addresses[0]));
    uint16_t size = is_end ? (remaining * sizeof(addresses->addresses[0])) : sizeof(addresses->addresses);

    memmove(g_record_descs + g_desc_count, &addresses->addresses, size);

    if (is_end) {
        t_result_message *res = (t_result_message *)&data->buffer[0];

        res->type = ERR_NONE;
        res->size = 0;

        data->size = result_message_get_buffer_size(res);
        data->state = 0;
        
        g_desc_list_idx = 1;
        g_current_desc_pos = 0;

        g_block_pos = 0;
        g_block.addr = g_record_descs[0].address;
    }
}

static bool flasher_cmd_header(t_ep_data *data) {
    memmove(&g_header, &data->buffer[0], sizeof(g_header));
    
    g_dest = g_header.dest;
    g_enhanced = false;

    prog_enter(g_dest, g_enhanced);
    prog_erase();

    if (!g_header.address_count) {
        t_result_message *res = (t_result_message *)&data->buffer[0];
        t_prog_row config;

        prog_set_config(&g_header.config);
        prog_exit(g_dest);
        
        prog_enter(g_dest, g_enhanced);
        prog_get_config(&config);
        prog_exit(g_dest);

        if (memcmp(&config, &g_header.config, sizeof(config))) {
            res->type = ERR_FLASHER_CONFIG_NOT_MATCH;
            res->size = (uint8_t)snprintf(
                &res->message[0],
                RESULT_BUF_SZ,
                "Written config does not match: [%lX, %lX, %lX, %lX]",
                config.w1,
                config.w2,
                config.w3,
                config.w4
            );
        } else {
            res->type = ERR_NONE;
            res->size = 0;
        }

        data->size = result_message_get_buffer_size(res);
        data->state = 0;

        return true;
    }

    data->state = g_header.address_count ? 1 : 2;

    if (g_record_descs) {
        free(g_record_descs);
    }

    g_record_descs = malloc(g_header.address_count * sizeof(g_header.addresses[0]));

    g_desc_count = sizeof(g_header.addresses) / sizeof(g_header.addresses[0]);
    memmove(g_record_descs, g_header.addresses, sizeof(g_header.addresses));

    return false;
}

static bool flasher_cmd_read_program(t_ep_data *data) {
    switch (data->state) {
        case 0: {
            if (data->size < sizeof(g_read)) {
                t_result_message *res = (t_result_message *)&data->buffer;

                res->type = ERR_BAD_INPUT_SIZE;
                res->size = (uint8_t)snprintf(
                    &res->message[0],
                    RESULT_BUF_SZ,
                    "Bad command size: %u < %u",
                    data->size,
                    (unsigned)sizeof(g_read)
                );

                data->size = result_message_get_buffer_size(res);

                return true;
            }

            led_prog(true);
            memset(&g_block, 0, sizeof(g_block));
            memmove(&g_read, &data->buffer[0], sizeof(g_read));

            t_result_words *res = (t_result_words *)&data->buffer[0];
            bool is_last = g_read.count < RECORD_WORD_COUNT;
            uint8_t count = is_last ? (uint8_t)g_read.count : RECORD_WORD_COUNT;

            res->type = RESULT_TYPE_VALUE;

            prog_enter(g_read.dest, false);

            g_block.addr = g_read.address;
            prog_read_block(&g_block);

            memmove(&res->words[0], &g_block.rows, sizeof(res->words));
            data->size = ((uint16_t)count * sizeof(res->words[0])) + sizeof(res->type);

            if (is_last) {
                prog_exit(g_read.dest);

                return true;
            }

            g_record_pos = RECORD_WORD_COUNT;
            g_block_pos = RECORD_WORD_COUNT;
            data->state = 1;

            break;
        }
        
        case 1: {
            t_result_words *res = (t_result_words *)&data->buffer[0];

            uint16_t record_remaining = g_read.count - g_record_pos;
            uint8_t block_remaining = PROG_BLOCK_WORD_COUNT - g_block_pos;

            bool is_last = record_remaining < RECORD_WORD_COUNT;
            uint8_t count = is_last ? (uint8_t)record_remaining : RECORD_WORD_COUNT;

            bool need_load = block_remaining < count;
            uint8_t w_cnt = need_load ? block_remaining : count;

            res->type = RESULT_TYPE_VALUE;
            memmove(&res->words[0], &g_block.rows[g_block_pos], w_cnt * sizeof(t_word));

            g_block_pos += w_cnt;
            g_record_pos += (uint16_t)w_cnt;

            if (need_load) {
                g_block_pos = RECORD_WORD_COUNT - w_cnt;

                g_block.addr = g_read.address + g_record_pos;
                prog_read_block(&g_block);

                memmove(&res->words[w_cnt], &g_block.rows[0], g_block_pos * sizeof(t_word));
                g_record_pos += (uint16_t)g_block_pos;
            } else {
                g_record_pos += (uint16_t)count;
            }

            data->size = ((uint16_t)count * sizeof(res->words[0])) + sizeof(res->type);
            if (is_last) {
                prog_exit(g_read.dest);
                data->state = 0;

                return true;
            }
        }
        
        default:
            make_bad_state_result(data);
            return true;
    }

    return false;
}

static bool flasher_cmd_read_config(t_ep_data *data) {
    t_result_config *res = (t_result_config *)&data->buffer[0];
    t_prog_row row;

    prog_enter(g_read.dest, false);
    prog_get_config(&row);
    prog_exit(g_read.dest);

    res->type = RESULT_TYPE_VALUE;
    res->config = row;

    return true;
}

static bool flasher_cmd_exit(t_ep_data *data) {
    prog_exit(g_dest);

    t_result_message *res = (t_result_message *)&data->buffer[0];

    res->type = ERR_NONE;
    res->size = 0;

    data->size = result_message_get_buffer_size(res);

    return true;
}

static char msg[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ--1234567890/abcdefghijk==1234567890**1234567890##1234567890::1234567890..abcdefghijklmnopqrstuvwxyz(1234567890)&1234567890";
static char buffer[4096] = {0};
static uint16_t bufpos = 0;
static uint16_t bufsz = 0;

static bool flasher_cmd_send_message(t_ep_data *data) {
    uint16_t sz = bufsz - bufpos;

    if (sz > (USBGEN_EP_SIZE - 2))
        sz = USBGEN_EP_SIZE - 2;

    data->buffer[0] = 0;
    data->buffer[1] = (uint8_t)sz;
    memmove(&data->buffer[2], &buffer[bufpos], sz);
    data->size = sz + 2;

    bufpos += sz;
    
    return bufpos >= bufsz;
}

static bool flasher_cmd_inspect(t_ep_data *data) {
    uint16_t size = strlen(msg);

    bufpos = 0;
    bufsz = size + 2;
    memmove(&buffer[0], &size, 2);
    memmove(&buffer[2], &msg[0], size);

    data->cmd = 6;
    data->state = 1;

    return flasher_cmd_send_message(data);
}


// Callbacks
static t_callback flasher_callbacks[] = {
    flasher_cmd_header,
    flasher_cmd_record,
    flasher_cmd_exit,
    flasher_cmd_read_program,
    flasher_cmd_read_config,
    flasher_cmd_send_message,
    flasher_cmd_inspect,
};

// Endpoint data
t_ep_data flasher = {
    .ep = FLASHER_EP,
    .callback_count = sizeof(flasher_callbacks) / sizeof(flasher_callbacks[0]),
    .callbacks = flasher_callbacks
};

t_ep_data *get_flasher_data() {
    return &flasher;
}
