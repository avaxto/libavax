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

#include "avaxto/wallet/hd_wallet_abstract.hpp"

namespace avaxto {
namespace wallet {

hd_wallet_abstract::hd_wallet_abstract(const LIBBITCOIN_PREFIX::wallet::hd_private& account_key)
    : account_key_(account_key), 
      internal_scan_(hd_scanner(account_key, true)),
      external_scan_(hd_scanner(account_key, false)) {
    
}

uint32_t hd_wallet_abstract::get_external_index() const {
    return external_scan_.get_index();
}

uint32_t hd_wallet_abstract::get_internal_index() const {
    return internal_scan_.get_index();
}

void hd_wallet_abstract::set_hd_indices(uint32_t external, uint32_t internal) {
    external_scan_.set_index(external);
    internal_scan_.set_index(internal);
    emit_address_change();
    is_hd_ready_ = true;
    emit_hd_ready();
}

std::string hd_wallet_abstract::get_address_x()  {
    return external_scan_.get_address_x();
}

std::string hd_wallet_abstract::get_change_address_x()  {
    return internal_scan_.get_address_x();
}

std::string hd_wallet_abstract::get_address_p()  {
    return external_scan_.get_address_p();
}

std::vector<std::string> hd_wallet_abstract::get_external_addresses_x()  {
    return external_scan_.get_all_addresses(chain_type::x_chain);
}

std::vector<std::string> hd_wallet_abstract::get_internal_addresses_x()  {
    return internal_scan_.get_all_addresses(chain_type::x_chain);
}

std::vector<std::string> hd_wallet_abstract::get_all_addresses_x()  {
    auto external = get_external_addresses_x();
    auto internal = get_internal_addresses_x();
    external.insert(external.end(), internal.begin(), internal.end());
    return external;
}

std::vector<std::string> hd_wallet_abstract::get_external_addresses_p()  {
    return external_scan_.get_all_addresses(chain_type::p_chain);
}

std::vector<std::string> hd_wallet_abstract::get_all_addresses_p()  {
    return get_external_addresses_p();
}

std::string hd_wallet_abstract::get_address_at_index_external_x(uint32_t index)  {
    return external_scan_.get_address_for_index(index, chain_type::x_chain);
}

std::string hd_wallet_abstract::get_address_at_index_internal_x(uint32_t index)  {
    return internal_scan_.get_address_for_index(index, chain_type::x_chain);
}

std::string hd_wallet_abstract::get_address_at_index_external_p(uint32_t index)  {
    return external_scan_.get_address_for_index(index, chain_type::p_chain);
}

void hd_wallet_abstract::emit_address_change() {
    // TODO: Implement event emission if needed
}

void hd_wallet_abstract::emit_hd_ready() {
    // TODO: Implement event emission if needed
}

} // namespace wallet
} // namespace avalanche 