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

#include "avaxto/wallet/mnemonic_wallet.hpp"
#include "avaxto/libbitcoin.h"
#include "avaxto/crypto/randnr.h"
#include <bitcoin/system/math/crypto.hpp>
#include <bitcoin/system/math/hash.hpp>

namespace avaxto {
namespace wallet {

using namespace LIBBITCOIN_PREFIX;

mnemonic_wallet::mnemonic_wallet(const std::string& mnemonic, uint32_t account)
    : hd_wallet_abstract()  // Initialize base class first
    , encrypted_mnemonic_(mnemonic) {
    if (!validate_mnemonic(mnemonic)) {
        throw std::runtime_error("Invalid mnemonic phrase.");
    }

    // Convert mnemonic to seed
    auto mnemonic_words = split(mnemonic);
    const LIBBITCOIN_PREFIX::wallet::mnemonic mnm{mnemonic_words};
    auto seed = mnm.to_seed();
    seed_ = LIBBITCOIN_PREFIX::to_chunk(seed);

    // Create master key
    master_key_ = LIBBITCOIN_PREFIX::wallet::hd_private(seed_);

    // Derive account key for Avalanche chains (m/44'/9000'/n')
    account_key_ = LIBBITCOIN_PREFIX::wallet::hd_private(seed_)
                             .derive_private(44 | LIBBITCOIN_PREFIX::wallet::hd_first_hardened_key)
                             .derive_private(9000 | LIBBITCOIN_PREFIX::wallet::hd_first_hardened_key)
                             .derive_private(account | LIBBITCOIN_PREFIX::wallet::hd_first_hardened_key);

    // Derive account key for Ethereum (m/44'/60'/0'/0)    
    eth_account_key_ = LIBBITCOIN_PREFIX::wallet::hd_private(seed_)
                                 .derive_private(44 | LIBBITCOIN_PREFIX::wallet::hd_first_hardened_key)
                                 .derive_private(60 | LIBBITCOIN_PREFIX::wallet::hd_first_hardened_key)
                                 .derive_private(0 | LIBBITCOIN_PREFIX::wallet::hd_first_hardened_key)
                                 .derive_private(0);

    // Initialize base class account key    
    hd_wallet_abstract::account_key_ = account_key_;

    // Initialize scanners
    internal_scan_ = hd_scanner(account_key_, true);
    external_scan_ = hd_scanner(account_key_, false);

    // Initialize EVM wallet    
    evm_wallet_ = evm_wallet(to_chunk(eth_account_key_.secret()));

    // Store encrypted mnemonic using AES256 encryption (libbitcoin pattern)
    encrypted_mnemonic_ = encrypt_mnemonic(mnemonic);
}

// Encryption function following libbitcoin's AES256 pattern
std::string mnemonic_wallet::encrypt_mnemonic(const std::string& mnemonic) const {
    using namespace libbitcoin::system;
    
    // Create encryption key from master key (first 32 bytes)
    libbitcoin::aes_secret encryption_key;
    auto master_secret = master_key_.secret();
    std::copy(master_secret.begin(), master_secret.end(), encryption_key.begin());
    
    // Convert mnemonic to data
    auto mnemonic_data = to_chunk(mnemonic);
    
    // Pad to AES block size (16 bytes)
    while (mnemonic_data.size() % libbitcoin::aes256_block_size != 0) {
        mnemonic_data.push_back(0x00);
    }
    
    // Encrypt in blocks
    data_chunk encrypted_data;
    for (size_t i = 0; i < mnemonic_data.size(); i += libbitcoin::aes256_block_size) {
        libbitcoin::aes_block block;
        std::copy(mnemonic_data.begin() + i, 
                 mnemonic_data.begin() + i + libbitcoin::aes256_block_size,
                 block.begin());
        
        libbitcoin::aes256_encrypt(encryption_key, block);
        encrypted_data.insert(encrypted_data.end(), block.begin(), block.end());
    }
    
    return encode_base16(encrypted_data);
}

// Decryption function following libbitcoin's AES256 pattern  
std::string mnemonic_wallet::decrypt_mnemonic(const std::string& encrypted) const {
    using namespace libbitcoin::system;
    
    // Create decryption key from master key (first 32 bytes)
    libbitcoin::aes_secret decryption_key;
    auto master_secret = master_key_.secret();
    std::copy(master_secret.begin(), master_secret.end(), decryption_key.begin());
    
    // Decode hex data
    auto encrypted_data = decode_base16(encrypted);
    
    // Decrypt in blocks
    data_chunk decrypted_data;
    for (size_t i = 0; i < encrypted_data.size(); i += libbitcoin::aes256_block_size) {
        libbitcoin::aes_block block;
        std::copy(encrypted_data.begin() + i,
                 encrypted_data.begin() + i + libbitcoin::aes256_block_size, 
                 block.begin());
        
        libbitcoin::aes256_decrypt(decryption_key, block);
        decrypted_data.insert(decrypted_data.end(), block.begin(), block.end());
    }
    
    // Remove padding and convert back to string
    auto end = std::find(decrypted_data.begin(), decrypted_data.end(), 0x00);
    return std::string(decrypted_data.begin(), end);
}

std::shared_ptr<mnemonic_wallet> mnemonic_wallet::create() {
    auto mnemonic = generate_mnemonic_phrase();
    return from_mnemonic(mnemonic);
}

std::shared_ptr<mnemonic_wallet> mnemonic_wallet::from_mnemonic(const std::string& mnemonic) {
    return std::make_shared<mnemonic_wallet>(mnemonic);
}

std::string mnemonic_wallet::generate_mnemonic_phrase() {
    // TODO: Implement proper mnemonic generation
    return "swear dolphin rich item abandon foot magnet mobile inch visa casino program funny someone youth voice tag secret street absorb breeze day cinnamon limb";
}

bool mnemonic_wallet::validate_mnemonic(const std::string& mnemonic) {
    return true; // TODO: Implement proper validation
}

std::string mnemonic_wallet::get_mnemonic() const {
    return decrypt_mnemonic(encrypted_mnemonic_);
}

std::string mnemonic_wallet::get_evm_private_key_hex() const {
    return evm_wallet_.get_private_key_hex();
}

std::string mnemonic_wallet::derive_x_chain_address(uint32_t index)  {
    return external_scan_.get_address_for_index(index, chain_type::x_chain);
}

std::string mnemonic_wallet::derive_p_chain_address(uint32_t index)  {
    return external_scan_.get_address_for_index(index, chain_type::p_chain);
}

std::string mnemonic_wallet::derive_c_chain_address(uint32_t index)  {
    auto eth_key = eth_account_key_.derive_private(index).secret();

    return evm_wallet::derive_address_from_private_key(to_chunk(eth_key));
}

} // namespace wallet
} // namespace avalanche 