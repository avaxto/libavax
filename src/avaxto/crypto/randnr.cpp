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

#include "avaxto/crypto/randnr.h"
#include <fstream>
#include <iostream>

namespace avaxto {
    namespace crypto {
        constexpr char RANDOM_BYTES_FILENAME[] = "/dev/random";

        void fill_random_bytes(LIBBITCOIN_PREFIX::data_chunk& entropy){
            auto entropy_size = entropy.size();    
            std::ifstream ifs(RANDOM_BYTES_FILENAME, std::ios::binary);
            if (!ifs) {
                std::cerr << "Cannot open /dev/random" << std::endl;
                return;
            }
            ifs.read(reinterpret_cast<char *>(&entropy[0]), entropy_size);
        }    

        std::vector<unsigned char> avaxto_generate_privbytes(size_t bytesize){
            
            std::vector<unsigned char> ret(bytesize);
            std::ifstream randomFile(AVAXTO_RANDNUMBER_FILE, std::ios::in | std::ios::binary);
            if (!randomFile) {
                throw std::runtime_error("Failed to open /dev/random");
            }

            randomFile.read(reinterpret_cast<char*>(ret.data()), bytesize);

            if (!randomFile) {
                throw std::runtime_error("Failed to read from /dev/random");
            }
            return ret;
        }
    }
}