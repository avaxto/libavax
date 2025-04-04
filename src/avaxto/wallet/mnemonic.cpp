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

#include <bitcoin/system.hpp>
#include <bitcoin/system/wallet/mnemonic.hpp>
#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "avaxto/wallet/mnemonic.h"
#include "avaxto/crypto/randnr.h"

namespace avaxto {
    namespace wallet {

        constexpr int ENTROPY_SIZE = 32;
        constexpr int MAX_ZEROS = ENTROPY_SIZE / 4;

        std::string new_mnemonic() {
            constexpr int entropy_bytes{ENTROPY_SIZE};
            bc::data_chunk my_entropy(entropy_bytes);
            avaxto::crypto::fill_random_bytes(my_entropy);

            int zero_count = 0;
            for (const auto& x : my_entropy) {
                if (x == 0) zero_count++;
            }

            // simple safeguard against accidental all zero entropy
            if (zero_count > MAX_ZEROS) {
                throw std::runtime_error{"Bad entropy, too many zeros found. Try again."};
            }            

            const auto mnm_list = libbitcoin::wallet::create_mnemonic(my_entropy);
            std::string mnm_sentence;
            for (const auto& word : mnm_list) {
                mnm_sentence += word + " ";
            }
            boost::algorithm::trim(mnm_sentence);
            return mnm_sentence;
        }
    }
}
