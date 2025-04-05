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

#ifndef AVAXTO_NETWORK_CONNECTION
#define AVAXTO_NETWORK_CONNECTION

#include <stdbool.h>
#include <openssl/ssl.h>
#include <pthread.h>

struct avax_peer_connection {
    struct avax_host *peer;
    int fd;
    // if this is a beacon connection, remember which
    bool is_beacon;
    int beacon_index; 
    SSL *ssl;
    // mark true if host was live on last connection attempt
    bool responded_version; 
    bool responded_peer_list; 
    char *version_string;
    size_t pending_bytes;
    bool connected;
    uint64_t last_sent;
    uint64_t last_received;
    pthread_t conn_thread;
};

int avax_connect(const char *host, uint16_t port);
SSL *avax_upgrade_connection(int fd, SSL_CTX *ssl_ctx);
void avax_close_peer_connection(struct avax_peer_connection *conn);
int avax_connect(const char *host, uint16_t port);

#endif