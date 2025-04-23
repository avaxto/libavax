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

#ifndef LEDGER_WALLET_HPP
#define LEDGER_WALLET_HPP

#include "../mnemonic_wallet.hpp"
#include "provider.hpp"
#include <memory>
#include <string>

namespace wallet {
namespace ledger {

class ledger_wallet : public public_mnemonic_wallet {
public:
    ledger_wallet(const std::string& xpub_avm, const std::string& xpub_evm, int account_index);

    static void set_transport(const std::shared_ptr<transport>& transport);
    static std::shared_ptr<ledger_wallet> from_transport(const std::shared_ptr<transport>& transport, int account_index = 0);

    static std::string get_extended_public_key_evm_account(const std::shared_ptr<transport>& transport);
    static std::string get_extended_public_key_evm_address(const std::shared_ptr<transport>& transport, int account_index);
    static std::string get_extended_public_key_avm_account(const std::shared_ptr<transport>& transport, int account_index);

private:
    int account_index_;
    static std::shared_ptr<transport> transport_;
    static std::shared_ptr<provider> provider_;
    static std::string version_;
    static std::string provider_type_;
};

} // namespace ledger
} // namespace wallet

#endif // LEDGER_WALLET_HPP