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

#ifndef AVAXTO_NETWORK_BEACON_FUNCS
#define AVAXTO_NETWORK_BEACON_FUNCS

#include <string.h>
#include <stdint.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "connection.h"
#include "avaxto/network/host.h"

void avax_connect_beacons(struct avax_host avax_beacons[], size_t beacon_count, SSL_CTX *ctx);
void avax_disconnect_beacons(struct avax_peer_connection avax_beacons[], size_t beacon_count);

struct avax_host *avax_get_random_beacon(void);

/*
    Initialize and connect beacons.
*/
void avax_init_beacons();
void avax_stop_beacons();

#endif