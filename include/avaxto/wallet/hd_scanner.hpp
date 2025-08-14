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
#include <vector>
#include <unordered_map>
#include "avaxto/libbitcoin.h"
#include "avaxto/libglobals.h"

namespace avaxto {
namespace wallet {

enum class chain_type {
    x_chain,
    p_chain,
    c_chain
};

class hd_scanner {
public:
    // Constructor
    hd_scanner() = default;
    explicit hd_scanner(const LIBBITCOIN_PREFIX::wallet::hd_private& account_key, bool is_internal = true);

    // Assignment operators
    hd_scanner& operator=(const hd_scanner& other);
    hd_scanner& operator=(hd_scanner&& other) noexcept;

    // Index management
    uint32_t get_index() const;
    void set_index(uint32_t index);
    uint32_t increment();

    // Address getters
    std::string get_address_x() ;
    std::string get_address_p() ;

    // Address list getters
    std::vector<std::string> get_all_addresses(chain_type chain = chain_type::x_chain) ;
    std::vector<std::string> get_addresses_in_range(uint32_t start, uint32_t end, chain_type chain = chain_type::x_chain) ;

    // Address derivation
    std::string get_address_for_index(uint32_t index, chain_type chain = chain_type::x_chain);

private:
    uint32_t index_ = 0;
    std::unordered_map<uint32_t, LIBBITCOIN_PREFIX::wallet::hd_private> address_cache_;
    std::string change_path_;
    LIBBITCOIN_PREFIX::wallet::hd_private account_key_;

    // Private methods
    LIBBITCOIN_PREFIX::wallet::hd_private get_hd_key_for_index(uint32_t index);
    std::string get_address_from_public_key(const LIBBITCOIN_PREFIX::data_chunk& public_key, chain_type chain) ;
};

} // namespace wallet
} // namespace avaxto 