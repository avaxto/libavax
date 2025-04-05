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


#ifndef AVAXTO_LOG
#define AVAXTO_LOG

enum avax_log_message_type_e {
    AVAXTO_MESSAGE_INFO,
    AVAXTO_MESSAGE_ERROR,
    AVAXTO_MESSAGE_WARNING,
    AVAXTO_MESSAGE_DEBUG,
};

void avax_log(const char *msg, enum avax_log_message_type_e typ);



#endif