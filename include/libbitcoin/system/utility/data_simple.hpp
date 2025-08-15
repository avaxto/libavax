/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Simplified data types for libavax project
 * Contains only the essential types needed by the project
 */

#ifndef LIBBITCOIN_SYSTEM_DATA_SIMPLE_HPP
#define LIBBITCOIN_SYSTEM_DATA_SIMPLE_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <secp256k1.h>

namespace libbitcoin {
namespace system {

// Define a byte array of a specified length.
template <size_t Size>
using byte_array = std::array<uint8_t, Size>;

// Define arbitrary byte storage types.
typedef std::vector<uint8_t> data_chunk;
typedef std::queue<data_chunk> data_queue;
typedef std::vector<data_chunk> data_stack;

// EC key constants
constexpr size_t ec_secret_size = 32;
constexpr size_t ec_compressed_size = 33;
constexpr size_t ec_uncompressed_size = 65;
constexpr size_t short_hash_size = 20;
constexpr size_t hash_size = 32;

// EC key types
typedef byte_array<ec_secret_size> ec_secret;
typedef byte_array<ec_compressed_size> ec_compressed;
typedef byte_array<ec_uncompressed_size> ec_uncompressed;
typedef byte_array<short_hash_size> short_hash;
typedef byte_array<hash_size> hash_digest;

/**
 * Convert a byte array to a data_chunk.
 */
template <size_t Size>
data_chunk to_chunk(const byte_array<Size>& bytes);

/**
 * Convert various types to data_chunk.
 */
data_chunk to_chunk(const std::string& text);
data_chunk to_chunk(const data_chunk& data);

/**
 * Encode data as base16 (hex) string.
 */
std::string encode_base16(const data_chunk& data);

/**
 * Decode base16 (hex) string to data.
 */
data_chunk decode_base16(const std::string& encoded);

/**
 * Placeholder cryptographic functions
 * Note: These are simplified placeholders. In a real implementation,
 * you would use proper secp256k1 cryptography library.
 */
bool secret_to_public(ec_compressed& out, const ec_secret& secret);
bool secret_to_public(ec_uncompressed& out, const ec_secret& secret);

/**
 * Simple split function for strings
 */
std::vector<std::string> split(const std::string& str, char delimiter = ' ');

/**
 * Simple hash functions (placeholders)
 * In a real implementation, these would use proper cryptographic libraries
 */
short_hash simple_ripemd160_sha256(const data_chunk& data);
hash_digest simple_sha256(const data_chunk& data);

// Implementation of template functions
template <size_t Size>
data_chunk to_chunk(const byte_array<Size>& bytes)
{
    return data_chunk(bytes.begin(), bytes.end());
}

// Implementation of inline functions
inline data_chunk to_chunk(const std::string& text)
{
    return data_chunk(text.begin(), text.end());
}

inline data_chunk to_chunk(const data_chunk& data)
{
    return data;
}

inline std::string encode_base16(const data_chunk& data)
{
    std::ostringstream stream;
    stream << std::hex << std::setfill('0');
    for (const auto byte : data) {
        stream << std::setw(2) << static_cast<unsigned int>(byte);
    }
    return stream.str();
}

inline data_chunk decode_base16(const std::string& encoded)
{
    data_chunk result;
    if (encoded.length() % 2 != 0) {
        return result; // Invalid hex string
    }
    
    result.reserve(encoded.length() / 2);
    for (size_t i = 0; i < encoded.length(); i += 2) {
        const auto hex_byte = encoded.substr(i, 2);
        const auto byte = static_cast<uint8_t>(std::stoul(hex_byte, nullptr, 16));
        result.push_back(byte);
    }
    return result;
}

// Placeholder implementations for cryptographic functions
// WARNING: These are NOT secure implementations, they are just placeholders
// In a real application, you would use libsecp256k1 or similar
inline bool secret_to_public(ec_compressed& out, const ec_secret& secret)
{
    // Real secp256k1 implementation
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    if (!ctx) return false;
    
    secp256k1_pubkey pubkey;
    if (!secp256k1_ec_pubkey_create(ctx, &pubkey, secret.data())) {
        secp256k1_context_destroy(ctx);
        return false;
    }
    
    size_t output_len = ec_compressed_size;
    if (!secp256k1_ec_pubkey_serialize(ctx, out.data(), &output_len, &pubkey, SECP256K1_EC_COMPRESSED)) {
        secp256k1_context_destroy(ctx);
        return false;
    }
    
    secp256k1_context_destroy(ctx);
    return output_len == ec_compressed_size;
}

inline bool secret_to_public(ec_uncompressed& out, const ec_secret& secret)
{
    // Real secp256k1 implementation
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    if (!ctx) return false;
    
    secp256k1_pubkey pubkey;
    if (!secp256k1_ec_pubkey_create(ctx, &pubkey, secret.data())) {
        secp256k1_context_destroy(ctx);
        return false;
    }
    
    size_t output_len = ec_uncompressed_size;
    if (!secp256k1_ec_pubkey_serialize(ctx, out.data(), &output_len, &pubkey, SECP256K1_EC_UNCOMPRESSED)) {
        secp256k1_context_destroy(ctx);
        return false;
    }
    
    secp256k1_context_destroy(ctx);
    return output_len == ec_uncompressed_size;
}

// Simplified hash functions - NOT cryptographically secure!
inline short_hash simple_ripemd160_sha256(const data_chunk& data)
{
    // Real RIPEMD160(SHA256(data)) implementation using OpenSSL
    hash_digest sha256_result;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.data(), data.size());
    SHA256_Final(sha256_result.data(), &sha256);
    
    short_hash result;
    RIPEMD160_CTX ripemd160;
    RIPEMD160_Init(&ripemd160);
    RIPEMD160_Update(&ripemd160, sha256_result.data(), sha256_result.size());
    RIPEMD160_Final(result.data(), &ripemd160);
    
    return result;
}

// Real SHA256 implementation using OpenSSL
inline hash_digest simple_sha256(const data_chunk& data)
{
    hash_digest result;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.data(), data.size());
    SHA256_Final(result.data(), &sha256);
    return result;
}

// Simple string split function
inline std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    std::string current;
    for (char c : str) {
        if (c == delimiter) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}

} // namespace system
} // namespace libbitcoin

#endif // LIBBITCOIN_SYSTEM_DATA_SIMPLE_HPP
