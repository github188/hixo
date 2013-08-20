// Copyright [2013] [E7, ryuuzaki.uchiha@gmail.com]

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "buffer.h"


int hixo_create_buffer(hixo_buffer_t *p_buf, ssize_t capacity)
{
    int rslt;
    uint8_t *p_data;

    assert(NULL == p_buf->mp_data);
    if (capacity < 0) {
        goto ERROR;
    } else if (capacity > 0) {
        p_data = (uint8_t *)calloc(1, capacity);
        if (NULL == p_data) {
            goto ERROR;
        }

        p_buf->mp_data = p_data;
        p_buf->m_offset = 0;
        p_buf->m_size = 0;
        p_buf->m_capacity = capacity;
        dlist_init(&p_buf->m_node);
    } else {
        p_buf->mp_data = NULL;
        p_buf->m_offset = 0;
        p_buf->m_size = 0;
        p_buf->m_capacity = 0;
        dlist_init(&p_buf->m_node);
    }

    do {
        rslt = HIXO_OK;
        break;

ERROR:
        rslt = HIXO_ERROR;
        break;
    } while (0);

    return rslt;
}

int hixo_expand_buffer(hixo_buffer_t *p_buf)
{
    int rslt;
    uint8_t *p_data = NULL;
    ssize_t data_size = 2 * p_buf->m_capacity;

    assert(p_buf->m_capacity > 0);
    p_data = (uint8_t *)calloc(1, data_size);
    if (NULL == p_data) {
        goto ERROR;
    }

    (void)memcpy(p_data, p_buf->mp_data, p_buf->m_size);
    free(p_buf->mp_data);
    p_buf->mp_data = p_data;
    p_buf->m_capacity = data_size;

    do {
        rslt = HIXO_OK;
        break;

ERROR:
        rslt = HIXO_ERROR;
        break;
    } while (0);

    return rslt;
}

void hixo_destroy_buffer(hixo_buffer_t *p_buf)
{
    assert(NULL != p_buf->mp_data);
    free(p_buf->mp_data);
    p_buf->mp_data = NULL;

    return;
}
