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

#include "provider.hpp"

namespace wallet {
namespace ledger {

class obsidian_provider : public provider {
public:
    static std::shared_ptr<obsidian_provider> instance();
    
    provider_type get_type() const override { return provider_type::obsidian; }
    std::string get_version(const std::shared_ptr<transport>& t) override;
    
    std::pair<bc::system::data_chunk, bc::system::data_chunk> get_xpub(
        const std::shared_ptr<transport>& t,
        const std::string& path,
        bool show = false,
        const std::string& hrp = "avax",
        const std::string& chain_id = "") override;

    bc::system::data_chunk get_address(
        const std::shared_ptr<transport>& t,
        const std::string& path,
        bool show = false,
        const std::string& hrp = "avax",
        const std::string& chain_id = "") override;

    std::pair<bc::system::data_chunk, std::map<std::string, bc::system::data_chunk>> sign_hash(
        const std::shared_ptr<transport>& t,
        const bc::system::data_chunk& hash,
        const std::string& account_path,
        const std::vector<std::string>& signer_paths) override;

    std::map<std::string, bc::system::data_chunk> sign_tx(
        const std::shared_ptr<transport>& t,
        const bc::system::data_chunk& tx,
        const std::string& account_path,
        const std::vector<std::string>& signer_paths,
        const std::vector<std::string>& change_paths = {}) override;

    bool can_parse_tx(size_t tx_size, size_t signers_size, size_t change_paths_size) const override;

private:
    obsidian_provider() = default;
    static std::shared_ptr<obsidian_provider> instance_;
};

} // namespace ledger
} // namespace wallet