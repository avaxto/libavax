/*
 * Copyright (C) 2025 REKTBuilder 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef AVAXTO_NETWORK_SERIALIZE
#define AVAXTO_NETWORK_SERIALIZE

#include <stdlib.h>
#include <stdint.h>

#include "ip.h"
#include "fla.h"
#include "vla.h"

// initial serialized buffer size in KB
// defaults to a typical page
#define AVAX_SERIALIZED_BUF_SIZ (4 * 1024)

struct avax_serialized_buff {
    void *buf;
    size_t len;
    void *pos; // current position in buf
};

typedef struct avax_serialized_buff avax_csb_t;

#define avax_serialize_buf_len(csb) (csb->pos - csb->buf)
#define avax_serialize_realloc_size(csb, siz) (avax_serialize_buf_len(csb) + siz)
#define avax_serialize_requires_realloc(csb, siz) ((avax_serialize_buf_len(csb) + siz) > csb->len)

/*
    Create a new serialization buffer.
    If siz <= 0 then AVAX_SERIALIZED_BUF_SIZ is used for the initial buffer size.
*/
avax_csb_t *avax_serialize_new(size_t siz);
void avax_serialize_free(avax_csb_t *csb);
void avax_serialize_byte(avax_csb_t *buf, unsigned char *c);
void avax_serialize_short(avax_csb_t *buf, uint16_t *s);
void avax_serialize_int(avax_csb_t *buf, uint32_t *i);
void avax_serialize_long(avax_csb_t *buf, uint64_t *l);
void avax_serialize_ip(avax_csb_t *buf, struct avax_ip_address *ip);
void avax_serialize_fla(avax_csb_t *buf, struct avax_fixed_length_array *fla);
void avax_serialize_vla(avax_csb_t *buf, struct avax_variable_length_array *vla);
void avax_serialize_string(avax_csb_t *buf, char *s); // zero-terminated string

#endif