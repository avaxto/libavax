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

#ifndef TO_AVAX_AVALANCHE_WALLET_HD_HELPER_H
#define TO_AVAX_AVALANCHE_WALLET_HD_HELPER_H

#include <string>
#include <bitcoin/system/wallet/hd_key.hpp> // For libbitcoin-system's hd_key
#include <bitcoin/system/utility/data.hpp> // For libbitcoin-system's data_chunk
#include <bitcoin/system/wallet/hd_private.hpp>
#include <bitcoin/system/wallet/hd_public.hpp>
#include <iostream>

namespace avalanche::wallet {

class hd_helper {
public:
    static constexpr int index_range = 20; // A gap of at least 20 indexes is needed to claim an index unused
    static constexpr int scan_size = 100;  // The total number of UTXOs to look at initially to calculate last index
    static constexpr int scan_range = scan_size - index_range; // How many items are actually scanned

private:
    std::string chain_id;
    libbitcoin::system::wallet::hd_key master_key;
    std::string change_path;
    int hd_index = 0;
    bool is_public = false;
    bool is_fetch_utxo = false;
    bool is_init = false;

public:
    // Constructor
    hd_helper(const std::string& change_path,
              const libbitcoin::system::wallet::hd_key& master_key,
              const std::string& chain_id,
              bool is_public)
        : change_path(change_path), master_key(master_key), chain_id(chain_id), is_public(is_public) {
        is_fetch_utxo = false;
        is_init = false;
        hd_index = 0;
    }

    // Increment the HD index
    int increment() {
        return ++hd_index;
    }

    // Get the current address for the X-chain
    std::string get_address_x() const {
        return get_address_for_index(hd_index);
    }

    // Get the current address for the P-chain
    std::string get_address_p() const {
        return get_address_for_index(hd_index);
    }

    // Get the address for a specific index
    std::string get_address_for_index(int index) const {
        return get_address_for_index(index, 1); // Replace `1` with the actual network ID
    }

    // Get the address for a specific index and network ID
    std::string get_address_for_index(int index, int network_id) const {
        auto key = get_hd_key_for_index(index);
        auto public_key = key.point();
        auto addr_buf = libbitcoin::system::to_chunk(public_key);
        auto hrp = get_preferred_hrp(network_id);
        return bin_tools_address_to_string(hrp, chain_id, addr_buf);
    }

    // Get the HD key for a specific index
    libbitcoin::system::wallet::hd_key get_hd_key_for_index(int index) const {
        std::string path = change_path + "/" + std::to_string(index);
        return master_key.derive_path(path);
    }

    // Get the current address
    std::string get_current_address() const {
        return get_address_for_index(hd_index);
    }

    // Getters and setters
    int get_hd_index() const {
        return hd_index;
    }

    void set_hd_index(int index) {
        hd_index = index;
    }

    const std::string& get_change_path() const {
        return change_path;
    }

    void set_change_path(const std::string& path) {
        change_path = path;
    }

    const libbitcoin::system::wallet::hd_key& get_master_key() const {
        return master_key;
    }

    void set_master_key(const libbitcoin::system::wallet::hd_key& key) {
        master_key = key;
    }

    const std::string& get_chain_id() const {
        return chain_id;
    }

    void set_chain_id(const std::string& id) {
        chain_id = id;
    }

    bool is_public_key() const {
        return is_public;
    }

    void set_public_key(bool public_key) {
        is_public = public_key;
    }

    bool is_fetch_utxo_enabled() const {
        return is_fetch_utxo;
    }

    void set_fetch_utxo(bool fetch_utxo) {
        is_fetch_utxo = fetch_utxo;
    }

    bool is_initialized() const {
        return is_init;
    }

    void set_initialized(bool init) {
        is_init = init;
    }

private:
    // Placeholder for helper functions
    std::string get_preferred_hrp(int network_id) const {
        // Replace with actual implementation
        return "hrp";
    }

    std::string bin_tools_address_to_string(const std::string& hrp, const std::string& chain_id,
                                            const libbitcoin::system::data_chunk& addr_buf) const {
        // Replace with actual implementation
        return hrp + "-" + chain_id + "-" + libbitcoin::system::encode_base16(addr_buf);
    }
};

} // namespace to::avax::avalanche::wallet

#endif // TO_AVAX_AVALANCHE_WALLET_HD_HELPER_H