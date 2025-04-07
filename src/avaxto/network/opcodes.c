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

#include "avaxto/network/opcodes.h"

// REF: network/commands.go
char *cavax_network_opcode_name(enum CAVAX_NETWORK_OPCODES op){
	switch (op) {
        case CAVAX_OP_GETVERSION:
            return "get_version";
        case CAVAX_OP_VERSION:
            return "version";
        case CAVAX_OP_GETPEERLIST:
            return "get_peerlist";
        case CAVAX_OP_PEERLIST:
            return "peerlist";
        case CAVAX_OP_PING:
            return "ping";
        case CAVAX_OP_PONG:
            return "pong";
        case CAVAX_OP_GETACCEPTEDFRONTIER:
            return "get_accepted_frontier";
        case CAVAX_OP_ACCEPTEDFRONTIER:
            return "accepted_frontier";
        case CAVAX_OP_GETACCEPTED:
            return "get_accepted";
        case CAVAX_OP_ACCEPTED:
            return "accepted";
        case CAVAX_OP_GET:
            return "get";
        case CAVAX_OP_GETANCESTORS:
            return "get_ancestors";
        case CAVAX_OP_PUT:
            return "put";
        case CAVAX_OP_MULTIPUT:
            return "multi_put";
        case CAVAX_OP_PUSHQUERY:
            return "push_query";
        case CAVAX_OP_PULLQUERY:
            return "pull_query";
        case CAVAX_OP_CHITS:
            return "chits";
        default:
            return "Unknown Op";
	}
}
