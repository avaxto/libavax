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

#ifndef AVAXTO_RAWBUF
#define AVAXTO_RAWBUF

typedef struct avax_rawbuf {
	unsigned char *buf;
	long unsigned int buffer_size; // allocated size
	long unsigned int used_size; // used size
} avax_rawbuf;

avax_rawbuf *avax_rawbuf_new(long unsigned int size);
int avax_rawbuf_copy(avax_rawbuf *dest, avax_rawbuf *src);
void avax_rawbuf_free(avax_rawbuf *buf);

#endif
