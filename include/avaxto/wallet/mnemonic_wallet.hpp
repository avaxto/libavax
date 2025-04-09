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
#include <memory>
#include <bitcoin/system.hpp>
#include "hd_wallet_abstract.hpp"
#include "avaxto/wallet/evm_wallet.hpp"

namespace avaxto {
namespace wallet {

class mnemonic_wallet : public hd_wallet_abstract {
public:
    // Constructor
    explicit mnemonic_wallet(const std::string& mnemonic, uint32_t account = 0);

    // Static factory methods
    static std::shared_ptr<mnemonic_wallet> create();
    static std::shared_ptr<mnemonic_wallet> from_mnemonic(const std::string& mnemonic);
    static std::string generate_mnemonic_phrase();
    static bool validate_mnemonic(const std::string& mnemonic);

    // Getters
    std::string get_mnemonic() const;
    std::string get_evm_private_key_hex() const;

    // Chain-specific address derivation
    std::string derive_x_chain_address(uint32_t index) ;
    std::string derive_p_chain_address(uint32_t index) ;
    std::string derive_c_chain_address(uint32_t index) ;

private:
    evm_wallet evm_wallet_;
    LIBBITCOIN_PREFIX::data_chunk seed_;
    LIBBITCOIN_PREFIX::wallet::hd_private master_key_;
    LIBBITCOIN_PREFIX::wallet::hd_private account_key_;
    LIBBITCOIN_PREFIX::wallet::hd_private eth_account_key_;
    std::string encrypted_mnemonic_;
};

} // namespace wallet
} // namespace avalanche 