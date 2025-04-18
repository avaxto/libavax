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