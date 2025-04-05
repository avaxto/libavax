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

#ifndef AVAXTO_NETWORK_OPCODES
#define AVAXTO_NETWORK_OPCODES

#include "avaxto/avax_general.h"

enum AVAX_NETWORK_OPCODES {
    AVAX_OP_GETVERSION,
    AVAX_OP_VERSION,
    AVAX_OP_GETPEERLIST,
    AVAX_OP_PEERLIST,
    AVAX_OP_PING,
    AVAX_OP_PONG,
    AVAX_OP_GETACCEPTEDFRONTIER,
    AVAX_OP_ACCEPTEDFRONTIER,
    AVAX_OP_GETACCEPTED,
    AVAX_OP_ACCEPTED,
    AVAX_OP_GETANCESTORS,
    AVAX_OP_MULTIPUT,
    AVAX_OP_GET,
    AVAX_OP_PUT,
    AVAX_OP_PUSHQUERY,
    AVAX_OP_PULLQUERY,
    AVAX_OP_CHITS,
    AVAX_OP_LAST, // keep this at last pos. never used opcode
};

char *avax_network_opcode_name(enum AVAX_NETWORK_OPCODES op);

#define AVAX_NETWORK_OPCODES_COUNT (AVAX_OP_LAST - AVAX_OP_GETVERSION)

#endif