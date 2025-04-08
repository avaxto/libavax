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

#include <unistd.h> // remove

#include "avaxto/network/beacons.h"
#include "avaxto/network/beacon-funcs.h"
#include "avaxto/network/msg.h"
#include "avaxto/network/peer.h"

void avax_connect_beacons(struct avax_host avax_beacons[], size_t beacon_count, SSL_CTX *ctx) {

    for (size_t i = 0; i < beacon_count; i++) {

        avax_beacon_connections[i].responded_version = false; // assume beacon is down
        avax_beacon_connections[i].beacon_index = i;
        avax_beacon_connections[i].is_beacon = true;

        printf("Connecting to %s : %d ...\n", avax_beacons[i].ip, avax_beacons[i].port);
        
        int conn = avax_connect(avax_beacons[i].ip, avax_beacons[i].port);
        printf("Connected fd # %d. Upgrading ... \n", conn);
        SSL *avax_conn = avax_upgrade_connection(conn, ctx);
        printf("DONE Upgrading connection with %s encryption.\n", SSL_get_cipher(avax_conn));        
                
        avax_beacon_connections[i].fd = conn;        
        avax_beacon_connections[i].ssl = avax_conn;

        avax_peer_thread(avax_beacon_connections + i);
    }
}

void avax_disconnect_beacons(struct avax_peer_connection avax_beacons[], size_t beacon_count){
    for (size_t i=0;i<beacon_count;i++) {
        avax_close_peer_connection(avax_beacons + i);
    }
}

/*
    Load and connect beacons.
    Beacons are regular hosts, except they should be assumed more trustworthy.
*/
void avax_init_beacons() {

    SSL_CTX *ctx;
    const SSL_METHOD *method = TLS_client_method();

    for (size_t i=0;i<AVAX_BEACON_LIST_SIZE;i++) {

        size_t j = 0;

        // find the colon :
        char *port_ptr = 0;
        for (;j<strlen(avax_beacon_ips[i]);j++) {
            if (avax_beacon_ips[i][j] == ':') {
                port_ptr = &avax_beacon_ips[i][j] + 1;
                break;
            }
        }

        memcpy(avax_beacons[i].ip, avax_beacon_ips[i], (port_ptr - *(avax_beacon_ips + i) - 1));
        avax_beacons[i].port = (uint16_t) atoi(port_ptr);
        // TODO get id from string 
        // avax_beacons[i].id = AVAX_BEACON_ids[i]; // ID is read-only

        //printf("IP %s PORT %d ID %s\n", avax_beacons[i].ip, avax_beacons[i].port, avax_beacons[i].id);
        

    }


    printf("Loading %lu Beacons...\n", AVAX_BEACON_LIST_SIZE);       

    printf("Init SSL ... ");
    SSL_library_init();
    printf("DONE\n");

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    ctx = SSL_CTX_new(method);

    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    
    avax_connect_beacons(avax_beacons, AVAX_BEACON_LIST_SIZE, ctx);    
}


void avax_stop_beacons() {
    avax_disconnect_beacons(avax_beacon_connections, AVAX_BEACON_LIST_SIZE);
}

struct avax_host *avax_get_random_beacon(void) {
    return NULL;
}