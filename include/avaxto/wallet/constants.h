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

#ifndef AVAXTO_WALLET_CONSTANTS_H
#define AVAXTO_WALLET_CONSTANTS_H

// HD WALLET
// m / purpose' / coin_type' / account' / change / address_index

#include <string>
#include <chrono>

namespace avaxto {
    namespace wallet {

        // AVAX token constants
        const std::string AVAX_TOKEN_INDEX = "9000";
        const std::string AVAX_TOKEN_PATH = "m/44'/" + AVAX_TOKEN_INDEX + "'";
        const std::string AVAX_ACCOUNT_PATH = "m/44'/" + AVAX_TOKEN_INDEX + "'/0'"; // Change and index left out
        const std::string ETH_ACCOUNT_PATH = "m/44'/60'/0'";
        const std::string LEDGER_ETH_ACCOUNT_PATH = ETH_ACCOUNT_PATH + "/0/0";

        // HD wallet scanning constants
        constexpr int HD_SCAN_GAP_SIZE = 20; // a gap of at least 20 indexes is needed to claim an index unused
        constexpr int SCAN_SIZE = 70; // the total number of utxos to look at initially to calculate last index
        constexpr int HD_SCAN_LOOK_UP_WINDOW = 64; // Number of addresses to check with the explorer at a single call
        constexpr int SCAN_RANGE = SCAN_SIZE - HD_SCAN_GAP_SIZE; // How many items are actually scanned

        // Ledger constants
        constexpr std::chrono::milliseconds LEDGER_EXCHANGE_TIMEOUT = std::chrono::milliseconds(90'000);
        const std::string MIN_EVM_SUPPORT_V = "0.5.3";

        /**
         * In order to free the thread when deriving addresses, the execution will sleep every N addresses derived
         */
        constexpr int DERIVATION_SLEEP_INTERVAL = 200;
        
    }
  
}

#endif