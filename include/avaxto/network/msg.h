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

#ifndef AVAXTO_NETWORK_MSG
#define AVAXTO_NETWORK_MSG

#include "../rawbuf.h"
#include "opcodes.h"
#include "fields.h"

// current maximum fields in a network message
#define AVAX_MAX_NETWORK_FIELDS 5

struct avax_network_msg {
	enum AVAX_NETWORK_OPCODES op;
	avax_rawbuf raw_bufer;
    avax_rawbuf *field_data[AVAX_MAX_NETWORK_FIELDS];
	enum AVAX_NETWORK_FIELDS fields[AVAX_MAX_NETWORK_FIELDS];	
    unsigned char field_count;
};

struct avax_network_msg avax_network_messages[AVAX_NETWORK_OPCODES_COUNT];
struct avax_network_msg *avax_network_parse_message(avax_rawbuf *rawbuf);

#endif