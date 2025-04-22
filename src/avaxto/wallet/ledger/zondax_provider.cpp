#include "zondax_provider.hpp"
#include <stdexcept>

namespace wallet {
namespace ledger {

std::shared_ptr<zondax_provider> zondax_provider::instance_;

std::shared_ptr<zondax_provider> zondax_provider::instance() {
    if (!instance_) {
        instance_ = std::shared_ptr<zondax_provider>(new zondax_provider());
    }
    return instance_;
}

std::string zondax_provider::get_version(const std::shared_ptr<transport>& t) {
    auto app_info = t->get_app_info();
    return app_info.app_version;
}

std::pair<bc::system::data_chunk, bc::system::data_chunk> zondax_provider::get_xpub(
    const std::shared_ptr<transport>& t,
    const std::string& path,
    bool show,
    const std::string& hrp,
    const std::string& chain_id) {
    
    auto keys = t->get_extended_pubkey(path, show, hrp, chain_id);
    if (keys.return_code != 0x9000) {
        throw std::runtime_error(keys.error_message);
    }
    
    return {keys.public_key, keys.chain_code};
}

bc::system::data_chunk zondax_provider::get_address(
    const std::shared_ptr<transport>& t,
    const std::string& path,
    bool show,
    const std::string& hrp,
    const std::string& chain_id) {
    
    auto resp = t->get_address_and_pubkey(path, show, hrp, chain_id);
    if (resp.return_code != 0x9000) {
        throw std::runtime_error(resp.error_message);
    }
    
    return resp.public_key;
}

std::pair<bc::system::data_chunk, std::map<std::string, bc::system::data_chunk>> zondax_provider::sign_hash(
    const std::shared_ptr<transport>& t,
    const bc::system::data_chunk& hash,
    const std::string& account_path,
    const std::vector<std::string>& signer_paths) {
    
    auto resp = t->sign_hash(account_path, signer_paths, hash);
    if (resp.return_code != 0x9000) {
        throw std::runtime_error(resp.error_message);
    }
    
    return {resp.hash, resp.signatures};
}

std::map<std::string, bc::system::data_chunk> zondax_provider::sign_tx(
    const std::shared_ptr<transport>& t,
    const bc::system::data_chunk& tx,
    const std::string& account_path,
    const std::vector<std::string>& signer_paths,
    const std::vector<std::string>& change_paths) {
    
    if (!can_parse_tx(tx.size(), signer_paths.size(), change_paths.size())) {
        throw std::runtime_error("Transaction size too big");
    }
    
    auto signed_tx = t->sign(account_path, signer_paths, tx, change_paths);
    if (signed_tx.return_code != 0x9000) {
        throw std::runtime_error(signed_tx.error_message);
    }
    
    return signed_tx.signatures;
}

bool zondax_provider::can_parse_tx(size_t tx_size, size_t signers_size, size_t change_paths_size) const {
    const size_t ledger_msg_size = (signers_size + change_paths_size) * 9 + tx_size;
    const size_t ledger_limit = 8 * 1024; // Maximum limit we can send to ledger
    return ledger_msg_size <= ledger_limit;
}

} // namespace ledger
} // namespace wallet