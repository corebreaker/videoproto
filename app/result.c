#include "./result.h"

uint8_t result_message_get_buffer_size(t_result_message *res) {
    return res->size + sizeof(*res) - 1;
}
