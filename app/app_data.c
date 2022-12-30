#include <stdio.h>
#include "./app_data.h"
#include "./result.h"

void make_bad_state_result(t_ep_data *ep_data) {
    t_result_message *res = (t_result_message *)&ep_data->buffer[0];

    res->type = ERR_INTERNAL;
    res->size = (uint8_t)snprintf(
        &res->message[0],
        RESULT_BUF_SZ,
        "Bad state %u for command %u",
        (unsigned)ep_data->state,
        (unsigned)ep_data->cmd
    );

    ep_data->size = result_message_get_buffer_size(res);
    ep_data->state = 0;
    memmove(&ep_data->buffer, &res, ep_data->size);    
}
