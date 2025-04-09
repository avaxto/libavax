/* 
 * Based on:
 * Bitcoin cryptography library
 * Copyright (c) Project Nayuki
 * 
 * https://www.nayuki.io/page/bitcoin-cryptography-library
 * https://github.com/nayuki/Bitcoin-Cryptography-Library
 * 
 * With modifications
 * 
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <bitcoin/system.hpp>
#include "avaxto/libglobals.h"


/* 
 * Computes the Keccak-256 hash of a sequence of bytes. The hash value is 32 bytes long.
 * Provides just one static method.
 */
class keccak256 final {
	
	public: 
		static constexpr int HASH_LEN = 32;
		static void get_hash(const std::uint8_t msg[], std::size_t len, std::uint8_t hashResult[HASH_LEN]);
		static LIBBITCOIN_PREFIX::data_chunk get_hash(const LIBBITCOIN_PREFIX::data_chunk& data);

	private: 
		static constexpr int BLOCK_SIZE = 200 - HASH_LEN * 2;
		static constexpr int NUM_ROUNDS = 24;
		static void absorb(std::uint64_t state[5][5]);
		// Requires 0 <= i <= 63
		static std::uint64_t rotl64(std::uint64_t x, int i);
	
	
		keccak256() = delete;  // Not instantiable
	
	
	private: 
		static const unsigned char ROTATION[5][5];
	
};