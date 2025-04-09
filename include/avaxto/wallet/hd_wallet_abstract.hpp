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
#include <memory>
#include <bitcoin/system.hpp>
#include "hd_scanner.hpp"

namespace avaxto {
namespace wallet {

class hd_wallet_abstract {
public:
    // Constructor
    explicit hd_wallet_abstract() = default;
    explicit hd_wallet_abstract(const LIBBITCOIN_PREFIX::wallet::hd_private& account_key);
    virtual ~hd_wallet_abstract() = default;

    // Index management
    uint32_t get_external_index() const;
    uint32_t get_internal_index() const;
    void set_hd_indices(uint32_t external, uint32_t internal);

    // Address getters
    std::string get_address_x() ;
    std::string get_change_address_x() ;
    std::string get_address_p() ;

    // Address list getters
    std::vector<std::string> get_external_addresses_x() ;
    std::vector<std::string> get_internal_addresses_x() ;
    std::vector<std::string> get_all_addresses_x() ;
    std::vector<std::string> get_external_addresses_p() ;
    std::vector<std::string> get_all_addresses_p() ;

    // Address at index getters
    std::string get_address_at_index_external_x(uint32_t index) ;
    std::string get_address_at_index_internal_x(uint32_t index) ;
    std::string get_address_at_index_external_p(uint32_t index) ;

protected:
    hd_scanner internal_scan_;
    hd_scanner external_scan_;
    LIBBITCOIN_PREFIX::wallet::hd_private account_key_;

    bool is_hd_ready_ = false;

    // Protected methods
    void emit_address_change();
    void emit_hd_ready();
};

} // namespace wallet
} // namespace avalanche 