#pragma once

#include "evm_wallet.hpp"
#include "avaxto/libbitcoin.h"
#include <string>
#include <vector>

namespace avaxto {
namespace wallet {

class evm_wallet_readonly : public evm_wallet {
public:
    explicit evm_wallet_readonly(const LIBBITCOIN_PREFIX::ec_compressed& uncompressed_key);
    virtual ~evm_wallet_readonly() = default;

    // Override base class methods to make them readonly
    void sign_transaction(const eth_transaction& tx) override;
    std::string sign_message(const std::string& message) override;
    std::string sign_typed_data(const eth_typed_data& data, uint8_t version) override;

private:
    LIBBITCOIN_PREFIX::ec_compressed public_key_;
};

} // namespace wallet
} // namespace avaxto