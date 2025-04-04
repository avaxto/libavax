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

#include <openssl/sha.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>
#include <algorithm>
#include "avaxto/crypto/cb58.h"

namespace crypto {

    std::string base58_encode(const std::vector<uint8_t>& data) {
        std::vector<uint8_t> input(data);
        std::string result;
        int zero_count = 0;
    
        for (uint8_t byte : input) {
            if (byte == 0) {
                zero_count++;
            } else {
                break;
            }
        }
    
        std::vector<uint8_t> temp((input.size() - zero_count) * 138 / 100 + 1);
        int j = temp.size();
    
        for (size_t i = zero_count; i < input.size(); i++) {
            int carry = input[i];
            for (int k = temp.size() - 1; k >= 0; k--) {
                carry += 256 * temp[k];
                temp[k] = carry % 58;
                carry /= 58;
            }
        }
    
        auto it = std::find_if(temp.begin(), temp.end(), [](uint8_t c) { return c != 0; });
        while (it != temp.end()) {
            result += BASE58_ALPHABET[*it++];
        }
    
        for (int i = 0; i < zero_count; i++) {
            result.insert(result.begin(), '1');
        }
    
        return result;
    }
    
    // Function to decode Base58 string to data
    std::vector<uint8_t> base58_decode(const std::string& str) {
        std::vector<uint8_t> result;
        if (str.empty()) {
            return result;
        }
    
        std::vector<uint8_t> temp(str.size() * 733 / 1000 + 1);
        int zero_count = 0;
    
        for (char c : str) {
            if (c == '1') {
                zero_count++;
            } else {
                break;
            }
        }
    
        for (char c : str) {
            const char* p = std::strchr(BASE58_ALPHABET, c);
            if (p == nullptr) {
                throw std::runtime_error("Invalid Base58 character");
            }
            int carry = p - BASE58_ALPHABET;
            for (int j = temp.size() - 1; j >= 0; j--) {
                carry += 58 * temp[j];
                temp[j] = carry % 256;
                carry /= 256;
            }
        }
    
        auto it = std::find_if(temp.begin(), temp.end(), [](uint8_t c) { return c != 0; });
        result.assign(it, temp.end());
    
        for (int i = 0; i < zero_count; i++) {
            result.insert(result.begin(), 0);
        }
    
        return result;
    }
    
    // Function to concatenate bytes
    std::vector<uint8_t> concat_bytes(const std::vector<uint8_t>& data, const std::vector<uint8_t>& checksum) {
        std::vector<uint8_t> result(data);
        result.insert(result.end(), checksum.begin(), checksum.end());
        return result;
    }
    
    // Function to compute SHA-256 hash
    std::vector<uint8_t> sha256(const std::vector<uint8_t>& data) {
        std::vector<uint8_t> hash(SHA256_DIGEST_LENGTH);
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.data(), data.size());
        SHA256_Final(hash.data(), &sha256);
        return hash;
    }
    
    // Base58Check encoding
    std::string base58check_encode(const std::vector<uint8_t>& data) {
        std::vector<uint8_t> checksum = sha256(data);
        checksum = sha256(checksum);
        checksum.resize(4);
        std::vector<uint8_t> extended_data = concat_bytes(data, checksum);
        return base58_encode(extended_data);
    }
    
    // Base58Check decoding
    std::vector<uint8_t> base58check_decode(const std::string& str) {
        std::vector<uint8_t> decoded = base58_decode(str);
        if (decoded.size() < 4) {
            throw std::runtime_error("Invalid Base58Check string");
        }
        decoded.resize(decoded.size() - 4);
        return decoded;
    }
    
}

