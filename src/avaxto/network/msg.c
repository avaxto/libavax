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

 
#include "avaxto/network/msg.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct avax_network_msg avax_network_messages[] = {
    {
        AVAX_OP_GETVERSION,
        {
            NULL, 0, 0
        },
        {0},
        {0},
        0
    },
    {
        AVAX_OP_VERSION,
        {
            NULL, 0, 0
        },
        {0},
        {   
            AVAX_FIELD_NETWORKID, 
            AVAX_FIELD_NODEID, 
            AVAX_FIELD_MYTIME, 
            AVAX_FIELD_IP, 
            AVAX_FIELD_VERSIONSTR
        },
        5
    },
    {
        AVAX_OP_GETPEERLIST,
        {
            NULL, 0, 0
        },
        {0},
        {0},
        0
    },
    {
        AVAX_OP_PEERLIST,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_PEERS
        },
        1
    },
    {
        AVAX_OP_PING,
        {
            NULL, 0, 0
        },
        {0},
        {0},
        0
    },
    {
        AVAX_OP_PONG,
        {
            NULL, 0, 0
        },
        {0},
        {0},
        0
    },
    {
        AVAX_OP_GETACCEPTEDFRONTIER,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_DEADLINE,
        },
        3
    },
    {
        AVAX_OP_ACCEPTEDFRONTIER,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_CONTAINERID,
        },
        3
    },
    {
        AVAX_OP_GETACCEPTED,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_DEADLINE,
            AVAX_FIELD_CONTAINERIDS,
        },
        4
    },
    {
        AVAX_OP_ACCEPTED,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_CONTAINERIDS,            
        },
        3
    },
    {
        AVAX_OP_GETANCESTORS,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_DEADLINE,
            AVAX_FIELD_CONTAINERID,            
        },
        4
    },
    {
        AVAX_OP_MULTIPUT,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_MULTICONTAINERBYTES,            
        },
        3
    },
    {
        AVAX_OP_GET,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_DEADLINE,
            AVAX_FIELD_CONTAINERID,
        },
        4
    },
    {
        AVAX_OP_PUT,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_CONTAINERID,
            AVAX_FIELD_CONTAINERBYTES,
        },
        4
    },
    {
        AVAX_OP_PUSHQUERY,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_DEADLINE,
            AVAX_FIELD_CONTAINERID,
            AVAX_FIELD_CONTAINERBYTES,
        },
        5
    },
    {
        AVAX_OP_PULLQUERY,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_DEADLINE,
            AVAX_FIELD_CONTAINERID,            
        },
        4
    },
    {
        AVAX_OP_CHITS,
        {
            NULL, 0, 0
        },
        {0},
        {
            AVAX_FIELD_CHAINID,
            AVAX_FIELD_REQUESTID,
            AVAX_FIELD_CONTAINERIDS,            
        },
        3
    },
};


struct avax_network_msg *avax_network_parse_message(avax_rawbuf *rawbuf) {
    struct avax_network_msg *msg = calloc(1, sizeof(struct avax_network_msg));
    avax_rawbuf_copy(&(msg->raw_bufer), rawbuf);
    printf("avax_network_parse_message BUFFER IS %lu BYTES\n", msg->raw_bufer.buffer_size);
    return msg;
}