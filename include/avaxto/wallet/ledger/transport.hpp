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
#include <map>
#include <functional>
#include <bitcoin/system.hpp>

namespace wallet {
namespace ledger {

struct app_info {
    std::string app_name;
    std::string app_version;
    uint8_t flags;
};

struct app_config {
    std::string version;
};

struct key_result {
    bc::system::data_chunk public_key;
    bc::system::data_chunk chain_code;
    uint16_t return_code;
    std::string error_message;
};

struct address_result {
    bc::system::data_chunk public_key;
    uint16_t return_code;
    std::string error_message;
};

struct sign_result {
    std::map<std::string, bc::system::data_chunk> signatures;
    uint16_t return_code;
    std::string error_message;
};

class transport : public std::enable_shared_from_this<transport> {
public:
    virtual ~transport() = default;

    virtual void set_exchange_timeout(unsigned int timeout) = 0;
    virtual void on_disconnect(std::function<void()> callback) = 0;

    // App level commands
    virtual app_info get_app_info() = 0;
    virtual app_config get_app_configuration() = 0;

    // Key derivation commands
    virtual key_result get_extended_pubkey(
        const std::string& path,
        bool show = false,
        const std::string& hrp = "avax",
        const std::string& chain_id = "") = 0;

    virtual address_result get_address_and_pubkey(
        const std::string& path,
        bool show = false,
        const std::string& hrp = "avax",
        const std::string& chain_id = "") = 0;

    virtual bc::system::data_chunk get_wallet_address(
        const std::string& path,
        const std::string& hrp = "avax") = 0;

    virtual key_result get_wallet_extended_public_key(
        const std::string& path) = 0;

    // Transaction signing
    virtual sign_result sign_hash(
        const std::string& account_path,
        const std::vector<std::string>& signer_paths,
        const bc::system::data_chunk& hash) = 0;

    virtual sign_result sign(
        const std::string& account_path,
        const std::vector<std::string>& signer_paths,
        const bc::system::data_chunk& tx,
        const std::vector<std::string>& change_paths = {}) = 0;

    virtual sign_result sign_transaction(
        const std::string& account_path,
        const std::vector<std::string>& signer_paths,
        const bc::system::data_chunk& tx,
        const std::string& change_path = "") = 0;

protected:
    transport() = default;
};

} // namespace ledger
} // namespace wallet