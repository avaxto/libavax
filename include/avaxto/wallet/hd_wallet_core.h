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

#ifndef TO_AVAX_AVALANCHE_WALLET_HD_WALLET_CORE_H
#define TO_AVAX_AVALANCHE_WALLET_HD_WALLET_CORE_H

#include <string>
#include <bitcoin/system/wallet/hd_key.hpp> // For libbitcoin-system's hd_key
#include "hd_helper.h" // For hd_helper from the Avalanche Wallet project
#include "wallet_core.h" // Base class

namespace avalanche::wallet {

class hd_wallet_core : public wallet_core {
private:
    std::string chain_id;
    hd_helper internal_helper;
    hd_helper external_helper;
    hd_helper platform_helper;
    libbitcoin::system::wallet::hd_key account_node_xp;
    libbitcoin::system::wallet::hd_key eth_hd_node;
    bool is_hd_ready = false;
    std::string seed;

    libbitcoin::system::wallet::hd_key hd_key;

public:
    // Constructors
    hd_wallet_core(const libbitcoin::system::wallet::hd_key& account_hd_key,
                   const libbitcoin::system::wallet::hd_key& eth_hd_node,
                   bool is_public)
        : internal_helper("m/1", account_hd_key, "X", is_public),
          external_helper("m/0", account_hd_key, "X", is_public),
          platform_helper("m/0", account_hd_key, "P", is_public),
          account_node_xp(account_hd_key),
          eth_hd_node(eth_hd_node) {
        this->init(account_hd_key, eth_hd_node, is_public);
    }

    hd_wallet_core() = default;

    // Initialization method
    void init(const libbitcoin::system::wallet::hd_key& account_hd_key,
              const libbitcoin::system::wallet::hd_key& eth_hd_node,
              bool is_public) {
        internal_helper = hd_helper("m/1", account_hd_key, "X", is_public);
        external_helper = hd_helper("m/0", account_hd_key, "X", is_public);
        platform_helper = hd_helper("m/0", account_hd_key, "P", is_public);
        account_node_xp = account_hd_key;
        this->eth_hd_node = eth_hd_node;
    }

    // Getters and setters
    std::string get_current_address_avm() const {
        return external_helper.get_current_address();
    }

    std::string get_chain_id() const {
        return chain_id;
    }

    void set_chain_id(const std::string& chain_id) {
        this->chain_id = chain_id;
    }

    hd_helper get_internal_helper() const {
        return internal_helper;
    }

    void set_internal_helper(const hd_helper& internal_helper) {
        this->internal_helper = internal_helper;
    }

    hd_helper get_external_helper() const {
        return external_helper;
    }

    void set_external_helper(const hd_helper& external_helper) {
        this->external_helper = external_helper;
    }

    hd_helper get_platform_helper() const {
        return platform_helper;
    }

    void set_platform_helper(const hd_helper& platform_helper) {
        this->platform_helper = platform_helper;
    }

    libbitcoin::system::wallet::hd_key get_account_node_xp() const {
        return account_node_xp;
    }

    void set_account_node_xp(const libbitcoin::system::wallet::hd_key& account_node_xp) {
        this->account_node_xp = account_node_xp;
    }

    libbitcoin::system::wallet::hd_key get_eth_hd_node() const {
        return eth_hd_node;
    }

    void set_eth_hd_node(const libbitcoin::system::wallet::hd_key& eth_hd_node) {
        this->eth_hd_node = eth_hd_node;
    }

    bool is_hd_ready() const {
        return is_hd_ready;
    }

    void set_hd_ready(bool hd_ready) {
        is_hd_ready = hd_ready;
    }

    std::string get_seed() const {
        return seed;
    }

    void set_seed(const std::string& seed) {
        this->seed = seed;
    }

    libbitcoin::system::wallet::hd_key get_hd_key() const {
        return hd_key;
    }

    void set_hd_key(const libbitcoin::system::wallet::hd_key& hd_key) {
        this->hd_key = hd_key;
    }
};

} // namespace to::avax::avalanche::wallet

#endif // TO_AVAX_AVALANCHE_WALLET_HD_WALLET_CORE_H