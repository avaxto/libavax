#include "obsidian_provider.hpp"
#include <stdexcept>

namespace wallet {
namespace ledger {

std::shared_ptr<obsidian_provider> obsidian_provider::instance_;

std::shared_ptr<obsidian_provider> obsidian_provider::instance() {
    if (!instance_) {
        instance_ = std::shared_ptr<obsidian_provider>(new obsidian_provider());
    }
    return instance_;
}

std::string obsidian_provider::get_version(const std::shared_ptr<transport>& t) {
    auto config = t->get_app_configuration();
    return config.version;
}

std::pair<bc::system::data_chunk, bc::system::data_chunk> obsidian_provider::get_xpub(
    const std::shared_ptr<transport>& t,
    const std::string& path,
    bool show,
    const std::string& hrp,
    const std::string& chain_id) {
    
    auto keys = t->get_wallet_extended_public_key(path);
    return {keys.public_key, keys.chain_code};
}

bc::system::data_chunk obsidian_provider::get_address(
    const std::shared_ptr<transport>& t,
    const std::string& path,
    bool show,
    const std::string& hrp,
    const std::string& chain_id) {
    
    return t->get_wallet_address(path, hrp);
}

std::pair<bc::system::data_chunk, std::map<std::string, bc::system::data_chunk>> obsidian_provider::sign_hash(
    const std::shared_ptr<transport>& t,
    const bc::system::data_chunk& hash,
    const std::string& account_path,
    const std::vector<std::string>& signer_paths) {
    
    auto signatures = t->sign_hash(account_path, signer_paths, hash);
    return {hash, signatures};
}

std::map<std::string, bc::system::data_chunk> obsidian_provider::sign_tx(
    const std::shared_ptr<transport>& t,
    const bc::system::data_chunk& tx,
    const std::string& account_path,
    const std::vector<std::string>& signer_paths,
    const std::vector<std::string>& change_paths) {
    
    std::string change_path;
    if (!change_paths.empty()) {
        change_path = account_path + "/" + change_paths[0];
    }
    
    auto signed_tx = t->sign_transaction(account_path, signer_paths, tx, change_path);
    return signed_tx.signatures;
}

bool obsidian_provider::can_parse_tx(size_t tx_size, size_t signers_size, size_t change_paths_size) const {
    // Obsidian provider doesn't support transaction parsing
    return false;
}

} // namespace ledger
} // namespace wallet