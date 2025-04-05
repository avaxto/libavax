#include "hd_scanner.hpp"
#include <bitcoin/system.hpp>
#include "crypto/keccak256.h"


namespace avalanche {
namespace wallet {

using namespace bc::system;

hd_scanner::hd_scanner(const bc::system::wallet::hd_private& account_key, bool is_internal)
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

bc::system::wallet::hd_private hd_scanner::get_hd_key_for_index(uint32_t index) {
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
    auto public_key = key.to_public().point();
    return get_address_from_public_key(to_chunk(public_key), chain);
}

std::string hd_scanner::get_address_from_public_key(const data_chunk& public_key, chain_type chain)  {
    // TODO: Implement proper Avalanche address format
    // For now, we'll use Bitcoin P2PKH format as a placeholder
    short_hash hash = bitcoin_short_hash(public_key);
    data_chunk prefix;
    data_chunk address;
    
    switch (chain) {
        case chain_type::x_chain:
            prefix = to_chunk(0x00); // X-chain prefix
            break;
        case chain_type::p_chain:
            prefix = to_chunk(0x01); // P-chain prefix
            break;
        case chain_type::c_chain:
            prefix = to_chunk(0x02); // C-chain prefix
            break;
    }
    
    build_chunk(address, prefix, hash);
    return encode_base58(address);
}

void hd_scanner::build_chunk(data_chunk& result, const data_chunk& prefix, const short_hash& hash)  {
    result.clear();
    result.reserve(prefix.size() + hash.size());
    result.insert(result.end(), prefix.begin(), prefix.end());
    result.insert(result.end(), hash.begin(), hash.end());
}



} // namespace wallet
} // namespace avalanche 