#pragma once

#include "evm_wallet.hpp"
#include <bitcoin/system.hpp>
#include <string>
#include <vector>

namespace avalanche {
namespace wallet {

class evm_wallet_readonly : public evm_wallet {
public:
    explicit evm_wallet_readonly(const bc::system::ec_compressed& uncompressed_key);
    virtual ~evm_wallet_readonly() = default;

    // Override base class methods to make them readonly
    void sign_transaction(const eth_transaction& tx) override;
    std::string sign_message(const std::string& message) override;
    std::string sign_typed_data(const eth_typed_data& data, uint8_t version) override;

private:
    bc::system::ec_compressed public_key_;
};

} // namespace wallet
} // namespace avalanche