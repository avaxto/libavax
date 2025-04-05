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

 
#ifndef AVAXTO_IDS
#define AVAXTO_IDS

// long id, from 256 bit hashes
typedef unsigned char avax_id_t[32];

// short id, from 160 bit hashes
typedef unsigned char avax_short_id_t[20];

// id from short ids, e.g. NodeID-A6onFGyJjA37EZ7kYHANMR1PFRT8NmXrF
avax_short_id_t *avax_short_id_from_string(const char *str);

// id from long id string
avax_short_id_t *avax_id_from_string(const char *str);


#endif