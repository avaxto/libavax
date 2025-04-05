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

#ifndef AVAXTO_NETWORK_BEACONS
#define AVAXTO_NETWORK_BEACONS

#include <string.h>
#include <stdint.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "host.h"
#include "connect.h"
#include "connection.h"

// IP and ID lists copied from genesis/beacons.go
char *avax_beacon_ips[] = {
    "54.94.43.49:9651",
    "52.79.47.77:9651",
    "18.229.206.191:9651",
    "3.34.221.73:9651",
    "13.244.155.170:9651",
    "13.244.47.224:9651",
    "122.248.200.212:9651",
    "52.30.9.211:9651",
    "122.248.199.127:9651",
    "18.202.190.40:9651",
    "15.206.182.45:9651",
    "15.207.11.193:9651",
    "44.226.118.72:9651",
    "54.185.87.50:9651",
    "18.158.15.12:9651",
    "3.21.38.33:9651",
    "54.93.182.129:9651",
    "3.128.138.36:9651",
    "3.104.107.241:9651",
    "3.106.25.139:9651",
    "18.162.129.129:9651",
    "18.162.161.230:9651",
    "52.47.181.114:9651",
    "15.188.9.42:9651"
};

char *avax_beacon_ids[] = {
    "NodeID-A6onFGyJjA37EZ7kYHANMR1PFRT8NmXrF",
    "NodeID-6SwnPJLH8cWfrJ162JjZekbmzaFpjPcf",
    "NodeID-GSgaA47umS1px2ohVjodW9621Ks63xDxD",
    "NodeID-BQEo5Fy1FRKLbX51ejqDd14cuSXJKArH2",
    "NodeID-Drv1Qh7iJvW3zGBBeRnYfCzk56VCRM2GQ",
    "NodeID-DAtCoXfLT6Y83dgJ7FmQg8eR53hz37J79",
    "NodeID-FGRoKnyYKFWYFMb6Xbocf4hKuyCBENgWM",
    "NodeID-Dw7tuwxpAmcpvVGp9JzaHAR3REPoJ8f2R",
    "NodeID-4kCLS16Wy73nt1Zm54jFZsL7Msrv3UCeJ",
    "NodeID-9T7NXBFpp8LWCyc58YdKNoowDipdVKAWz",
    "NodeID-6ghBh6yof5ouMCya2n9fHzhpWouiZFVVj",
    "NodeID-HiFv1DpKXkAAfJ1NHWVqQoojjznibZXHP",
    "NodeID-Fv3t2shrpkmvLnvNzcv1rqRKbDAYFnUor",
    "NodeID-AaxT2P4uuPAHb7vAD8mNvjQ3jgyaV7tu9",
    "NodeID-kZNuQMHhydefgnwjYX1fhHMpRNAs9my1",
    "NodeID-A7GwTSd47AcDVqpTVj7YtxtjHREM33EJw",
    "NodeID-Hr78Fy8uDYiRYocRYHXp4eLCYeb8x5UuM",
    "NodeID-9CkG9MBNavnw7EVSRsuFr7ws9gascDQy3",
    "NodeID-A8jypu63CWp76STwKdqP6e9hjL675kdiG",
    "NodeID-HsBEx3L71EHWSXaE6gvk2VsNntFEZsxqc",
    "NodeID-Nr584bLpGgbCUbZFSBaBz3Xum5wpca9Ym",
    "NodeID-QKGoUvqcgormCoMj6yPw9isY7DX9H4mdd",
    "NodeID-HCw7S2TVbFPDWNBo1GnFWqJ47f9rDJtt1",
    "NodeID-FYv1Lb29SqMpywYXH7yNkcFAzRF2jvm3K"
};

#define AVAX_BEACON_IP_LEN(bcon) (bcon.port_ptr - bcon.ip_ptr)
#define AVAX_BEACON_LIST_SIZE (sizeof(avax_beacon_ips) / sizeof(avax_beacon_ips[0]))

struct avax_host avax_beacons[AVAX_BEACON_LIST_SIZE];
struct avax_peer_connection avax_beacon_connections[AVAX_BEACON_LIST_SIZE]; /* Static size beacon list. */

#endif