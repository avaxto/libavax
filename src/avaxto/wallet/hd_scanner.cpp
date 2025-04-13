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

#include <bitcoin/system.hpp>
#include "avaxto/wallet/hd_scanner.hpp"
#include "avaxto/crypto/keccak256.h"
#include "avaxto/crypto/bech32.h"

namespace avaxto {
namespace wallet {

hd_scanner::hd_scanner(const LIBBITCOIN_PREFIX::wallet::hd_private& account_key, bool is_internal)
    : account_key_(account_key) {
    change_path_ = is_internal ? "1" : "0";
}

hd_scanner& hd_scanner::operator=(const hd_scanner& other) {
    if (this != &other) {
        index_ = other.index_;
        address_cache_ = other.address_cache_;
        change_path_ = other.change_path_;
        account_key_ = other.account_key_;
    }
    return *this;
}

hd_scanner& hd_scanner::operator=(hd_scanner&& other) noexcept {
    if (this != &other) {
        index_ = std::exchange(other.index_, 0);
        address_cache_ = std::move(other.address_cache_);
        change_path_ = std::move(other.change_path_);
        account_key_ = std::move(other.account_key_);
    }
    return *this;
}

uint32_t hd_scanner::get_index() const {
    return index_;
}

void hd_scanner::set_index(uint32_t index) {
    if (index < 0) {
        throw std::runtime_error("Index must be >= 0");
    }
    index_ = index;
}

uint32_t hd_scanner::increment() {
    return index_++;
}

std::string hd_scanner::get_address_x()  {
    return get_address_for_index(index_, chain_type::x_chain);
}

std::string hd_scanner::get_address_p()  {
    return get_address_for_index(index_, chain_type::p_chain);
}

std::vector<std::string> hd_scanner::get_all_addresses(chain_type chain)  {
    return get_addresses_in_range(0, index_ + 1, chain);
}

std::vector<std::string> hd_scanner::get_addresses_in_range(uint32_t start, uint32_t end, chain_type chain)  {
    std::vector<std::string> addresses;
    addresses.reserve(end - start);
    
    for (uint32_t i = start; i < end; ++i) {
        addresses.push_back(get_address_for_index(i, chain));
    }
    
    return addresses;
}

LIBBITCOIN_PREFIX::wallet::hd_private hd_scanner::get_hd_key_for_index(uint32_t index) {
    auto it = address_cache_.find(index);
    if (it != address_cache_.end()) {
        return it->second;
    }

    auto key = account_key_.derive_private(std::stoul(change_path_))
                          .derive_private(index);
    address_cache_[index] = key;
    return key;
}

std::string hd_scanner::get_address_for_index(uint32_t index, chain_type chain) {
    auto key = get_hd_key_for_index(index);
    auto xkpb = key.secret();
    auto public_key = key.to_public().point();
    return get_address_from_public_key(LIBBITCOIN_PREFIX::to_chunk(public_key), chain);
}

std::string hd_scanner::get_address_from_public_key(const LIBBITCOIN_PREFIX::data_chunk& public_key, chain_type chain)  {

    LIBBITCOIN_PREFIX::short_hash hash = LIBBITCOIN_PREFIX::bitcoin_short_hash(public_key);    

    std::string prefix;    
    switch (chain) {
        case chain_type::x_chain:
            prefix = "X-";
            break;
        case chain_type::p_chain:
            prefix = "P-";
            break;
        case chain_type::c_chain:
            prefix = "0x";
            break;
    }
    
    std::vector<uint8_t> enc;
    enc.push_back(0);
    std::vector<unsigned char> const& tch = LIBBITCOIN_PREFIX::to_chunk(hash);
    bech32::convertbits<8, 5, true>(enc, tch);    
    // enc esta ok
    const auto bc32 = bech32::Encode(bech32::Encoding::BECH32, AVAX_BECH32_HRP, enc);

    std::stringstream addr_str;
    addr_str << prefix;
    addr_str << bc32;
    return addr_str.str();
}


} // namespace wallet
} // namespace avalanche 