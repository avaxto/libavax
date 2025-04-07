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

#include <stdio.h>
#include <stdlib.h>
#include "avaxto/network/network.h"

/* 
    The default network object.    
    This private structure lives throughout the avaxto process lifetime.
*/

static struct avax_network _avax_default_network;

void avax_network_listen() {
    // TODO Listen for inbound connections.    
}

void avax_start_network() {
    printf("Starting avaxto Network...");
    if (_avax_default_network.connections == NULL) {
        _avax_default_network.connections = calloc(1, AVAX_INITIAL_CONNECTION_POOL_SIZE * sizeof(struct avax_peer_connection));
    }    
    
    printf("DONE");
}

