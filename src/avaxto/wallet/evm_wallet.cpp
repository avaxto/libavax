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

#include "evm_wallet.hpp"
#include <bitcoin/system.hpp>
#include <bitcoin/system/crypto/secp256k1.hpp>
#include "crypto/keccak256.h"
namespace avalanche {
namespace wallet {

using namespace bc::system;

evm_wallet::evm_wallet(const data_chunk& private_key)
    : private_key_(private_key) {
    // Generate public key from private key
    ec_compressed point;

    ec_secret secret;
    std::copy(private_key.begin(), private_key.end(), secret.begin());

    secret_to_public(point, secret);
    public_key_ = to_chunk(point);

    // Generate Ethereum address
    address_ = public_key_to_address(public_key_);
}

std::string evm_wallet::get_private_key_hex() const {
    return encode_base16(private_key_);
}

std::string evm_wallet::get_address() const {
    return address_;
}

std::string evm_wallet::derive_address_from_private_key(const data_chunk& private_key) {
    ec_compressed point;
    ec_secret secret;
    std::copy(private_key.begin(), private_key.end(), secret.begin());

    secret_to_public(point, secret);
    return public_key_to_address(to_chunk(point));
}

std::string evm_wallet::public_key_to_address(const data_chunk& public_key) {
    // Remove the first byte (0x04) from uncompressed public key if present
    data_chunk key = public_key;
    if (key.size() == 65 && key[0] == 0x04) {
        key.erase(key.begin());
    }

    // Keccak-256 hash of the public key
    auto hash = keccak256::get_hash(key);

    // Take the last 20 bytes
    data_chunk address(hash.end() - 20, hash.end());

    // Return the address with "0x" prefix
    return "0x" + encode_base16(address);
}

} // namespace wallet
} // namespace avalanche 