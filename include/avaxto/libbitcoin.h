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

#ifndef AVAXTO_LIBBITCOIN_H
#define AVAXTO_LIBBITCOIN_H

#include <libbitcoin/system/utility/data_simple.hpp>

namespace avaxto {
namespace libbitcoin {

// Import the libbitcoin::system types into the avaxto::libbitcoin namespace
using data_chunk = ::libbitcoin::system::data_chunk;
using data_queue = ::libbitcoin::system::data_queue;
using data_stack = ::libbitcoin::system::data_stack;

// Import EC key types
using ec_secret = ::libbitcoin::system::ec_secret;
using ec_compressed = ::libbitcoin::system::ec_compressed;
using ec_uncompressed = ::libbitcoin::system::ec_uncompressed;

// Import utility functions
using ::libbitcoin::system::to_chunk;
using ::libbitcoin::system::encode_base16;
using ::libbitcoin::system::decode_base16;
using ::libbitcoin::system::secret_to_public;

} // namespace libbitcoin
} // namespace avaxto

#endif // AVAXTO_LIBBITCOIN_H
