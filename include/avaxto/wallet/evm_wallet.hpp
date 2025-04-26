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

#pragma once

#include <string>
#include <bitcoin/system.hpp>
#include "avaxto/libglobals.h"

namespace avaxto {
namespace wallet {

class evm_wallet {
public:
    // Constructor
    evm_wallet() = default;
    explicit evm_wallet(const LIBBITCOIN_PREFIX::data_chunk& private_key);

    // Getters
    std::string get_private_key_hex() const;
    std::string get_address() const;

    // Address derivation
    static std::string derive_address_from_private_key(const LIBBITCOIN_PREFIX::data_chunk& private_key);

private:
    LIBBITCOIN_PREFIX::data_chunk private_key_;
    LIBBITCOIN_PREFIX::data_chunk public_key_;
    std::string address_;

    // Private methods
    static std::string public_key_to_address(const LIBBITCOIN_PREFIX::data_chunk& public_key);
};

} // namespace wallet
} // namespace avalanche 