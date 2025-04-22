#pragma once

#include <memory>
#include <string>
#include <map>
#include <bitcoin/system.hpp>
#include "transport.hpp"

namespace wallet {
namespace ledger {

enum class provider_type {
    obsidian,
    zondax
};

class provider {
public:
    virtual ~provider() = default;

    virtual provider_type get_type() const = 0;
    virtual std::string get_version(const std::shared_ptr<transport>& t) = 0;

    virtual std::pair<bc::system::data_chunk, bc::system::data_chunk> get_xpub(
        const std::shared_ptr<transport>& t,
        const std::string& path,
        bool show = false,
        const std::string& hrp = "avax",
        const std::string& chain_id = "") = 0;

    virtual bc::system::data_chunk get_address(
        const std::shared_ptr<transport>& t,
        const std::string& path,
        bool show = false,
        const std::string& hrp = "avax",
        const std::string& chain_id = "") = 0;

    virtual std::pair<bc::system::data_chunk, std::map<std::string, bc::system::data_chunk>> sign_hash(
        const std::shared_ptr<transport>& t,
        const bc::system::data_chunk& hash,
        const std::string& account_path,
        const std::vector<std::string>& signer_paths) = 0;

    virtual std::map<std::string, bc::system::data_chunk> sign_tx(
        const std::shared_ptr<transport>& t,
        const bc::system::data_chunk& tx,
        const std::string& account_path,
        const std::vector<std::string>& signer_paths,
        const std::vector<std::string>& change_paths = {}) = 0;

    virtual bool can_parse_tx(size_t tx_size, size_t signers_size, size_t change_paths_size) const = 0;

protected:
    provider() = default;
};

} // namespace ledger
} // namespace wallet