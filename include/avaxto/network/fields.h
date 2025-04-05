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

#ifndef AVAXTO_NETWORK_FIELDS
#define AVAXTO_NETWORK_FIELDS



enum AVAX_NETWORK_FIELDS {
    AVAX_FIELD_VERSIONSTR,
    AVAX_FIELD_NETWORKID,
    AVAX_FIELD_NODEID,
    AVAX_FIELD_MYTIME,
    AVAX_FIELD_IP,
    AVAX_FIELD_PEERS,
    AVAX_FIELD_CHAINID,
    AVAX_FIELD_REQUESTID,
    AVAX_FIELD_DEADLINE,
    AVAX_FIELD_CONTAINERID,
    AVAX_FIELD_CONTAINERBYTES,
    AVAX_FIELD_CONTAINERIDS,
    AVAX_FIELD_MULTICONTAINERBYTES,
};

char *avax_network_field_name(enum AVAX_NETWORK_FIELDS f);

#endif