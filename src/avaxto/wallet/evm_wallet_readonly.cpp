#include "evm_wallet_readonly.hpp"
#include <stdexcept>

namespace avalanche {
namespace wallet {

evm_wallet_readonly::evm_wallet_readonly(const bc::system::ec_compressed& uncompressed_key)
    : public_key_(uncompressed_key) {}

void evm_wallet_readonly::sign_transaction(const eth_transaction& tx) {
    throw std::runtime_error("Cannot sign transactions with readonly wallet");
}

std::string evm_wallet_readonly::sign_message(const std::string& message) {
    throw std::runtime_error("Cannot sign messages with readonly wallet");
}

std::string evm_wallet_readonly::sign_typed_data(const eth_typed_data& data, uint8_t version) {
    throw std::runtime_error("Cannot sign typed data with readonly wallet");
}

} // namespace wallet
} // namespace avalanche