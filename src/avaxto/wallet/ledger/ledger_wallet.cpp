#include "avaxto/wallet/ledger/ledger_wallet.hpp"
#include <bitcoin/system.hpp>
#include <iostream>
#include <stdexcept>

namespace wallet {
namespace ledger {

ledger_wallet::ledger_wallet(const std::string& xpub_avm, const std::string& xpub_evm, int account_index)
    : public_mnemonic_wallet(xpub_avm, xpub_evm), account_index_(account_index) {
    type_ = "ledger";
}

void ledger_wallet::set_transport(const std::shared_ptr<transport>& transport) {
    provider_ = get_ledger_provider(transport);
    transport_ = transport;

    transport_->on_disconnect([]() {
        std::cout << "Transport disconnected" << std::endl;
        transport_.reset();
    });

    version_ = provider_->get_version(transport_);
    provider_type_ = provider_->get_type();
}

std::shared_ptr<ledger_wallet> ledger_wallet::from_transport(const std::shared_ptr<transport>& transport, int account_index) {
    transport->set_exchange_timeout(LEDGER_EXCHANGE_TIMEOUT);

    auto pub_avm = get_extended_public_key_avm_account(transport, account_index);
    auto pub_evm = get_extended_public_key_evm_address(transport, account_index);

    set_transport(transport);
    return std::make_shared<ledger_wallet>(pub_avm, pub_evm, account_index);
}

std::string ledger_wallet::get_extended_public_key_evm_account(const std::shared_ptr<transport>& transport) {
    auto eth_app = get_app_eth(transport);
    auto eth_res = eth_app->get_address(ETH_ACCOUNT_PATH, false, true);

    bc::wallet::hd_private hd_eth(
        bc::data_chunk(eth_res.public_key.begin(), eth_res.public_key.end()),
        bc::data_chunk(eth_res.chain_code.begin(), eth_res.chain_code.end()));

    return hd_eth.to_string();
}

std::string ledger_wallet::get_extended_public_key_evm_address(const std::shared_ptr<transport>& transport, int account_index) {
    auto account_key = get_extended_public_key_evm_account(transport);
    return get_eth_address_key_from_account_key(account_key, account_index);
}

std::string ledger_wallet::get_extended_public_key_avm_account(const std::shared_ptr<transport>& transport, int account_index) {
    auto provider = get_ledger_provider(transport);
    auto res = provider->get_xpub(transport, get_account_path_avalanche(account_index));

    bc::wallet::hd_private hd_key(
        bc::data_chunk(res.pub_key.begin(), res.pub_key.end()),
        bc::data_chunk(res.chain_code.begin(), res.chain_code.end()));

    return hd_key.to_string();
}

} // namespace ledger
} // namespace wallet