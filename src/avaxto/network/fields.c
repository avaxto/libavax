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

#include "avaxto/network/fields.h"


char *avax_network_field_name(enum AVAX_NETWORK_FIELDS f){
	switch (f) {
        case AVAX_FIELD_VERSIONSTR:
            return "VersionStr";
        case AVAX_FIELD_NETWORKID:
            return "NetworkID";
        case AVAX_FIELD_NODEID:
            return "NodeID";
        case AVAX_FIELD_MYTIME:
            return "MyTime";
        case AVAX_FIELD_IP:
            return "IP";
        case AVAX_FIELD_PEERS:
            return "Peers";
        case AVAX_FIELD_CHAINID:
            return "ChainID";
        case AVAX_FIELD_REQUESTID:
            return "RequestID";
        case AVAX_FIELD_DEADLINE:
            return "Deadline";
        case AVAX_FIELD_CONTAINERID:
            return "ContainerID";
        case AVAX_FIELD_CONTAINERBYTES:
            return "Container Bytes";
        case AVAX_FIELD_CONTAINERIDS:
            return "Container IDs";
        case AVAX_FIELD_MULTICONTAINERBYTES:
            return "MultiContainerBytes";
        default:
            return "Unknown Field";
	}
}