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

#ifndef AVAXTO_AVAX
#define AVAXTO_AVAX

// constants from network/network.go
#define defaultInitialReconnectDelay 1
#define defaultMaxReconnectDelay     (60 * 60)
#define DefaultMaxMessageSize        (1 << 21)
#define defaultSendQueueSize         (1 << 10)
#define defaultMaxNetworkPendingSendBytes (1 << 29) // 512MB
#define defaultNetworkPendingSendBytesToRateLimit        (defaultMaxNetworkPendingSendBytes / 4)
#define defaultMaxClockDifference    60
#define defaultPeerListGossipSpacing 60
#define defaultPeerListGossipSize    100
#define defaultPeerListStakerGossipFraction 2
#define defaultGetVersionTimeout     2
#define defaultAllowPrivateIPs       true
#define defaultGossipSize            50
#define defaultPingPongTimeout       60
#define defaultPingFrequency         (3 * defaultPingPongTimeout / 4)


#endif