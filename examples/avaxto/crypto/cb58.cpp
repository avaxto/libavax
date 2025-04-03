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

#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include "crypto/cb58.h"

/*
    This example demos how to encode and decode a buffer to a base58 string.
    This is NOT a test case.
*/

struct AddressStruct {
    std::vector<uint8_t> buffer;
    std::string string;
    std::string checksum;
};

std::vector<AddressStruct> examples = {
    {
        {0x00, 0xfe, 0x7b, 0xd0, 0xe0, 0x03, 0x2b, 0x8d, 0x2c, 0x11, 0x56,
         0x84, 0x1f, 0xa0, 0x60, 0x14, 0x56, 0xaa, 0xac, 0x8f, 0x3c, 0x0e,
         0xf1, 0x6d, 0x8c},
        "1QCaxc8hutpdZ62iKZsn1TCG3nh7uPZojq",
        "13cp39pSRSMbaxjaXZfFLXuiiK4FHDBQRBm35ab2"
    },
    {
        {0x00, 0x8b, 0x46, 0xd2, 0x54, 0xa0, 0x83, 0xd1, 0x0c, 0xe3, 0xf1,
         0x2f, 0x5e, 0x95, 0x43, 0xba, 0x73, 0x1f, 0x21, 0xf2, 0xa9, 0x6f,
         0xeb, 0x2a, 0x60},
        "1DhRmSGnhPjUaVPAj48zgPV9e2oRhAQFUb",
        "12S5vHShaePQQAXjmjLC87s1Kxi9uM6YEkS2K5Hh"
    },
    {
        {0x00, 0x45, 0x7a, 0x36, 0xbb, 0x6b, 0xee, 0xe4, 0xea, 0xd3, 0x60,
         0x95, 0x37, 0xda, 0x65, 0x8c, 0x02, 0x62, 0x3e, 0xbe, 0x88, 0x08,
         0x6d, 0x18, 0xc7},
        "17LN2oPYRYsXS9TdYdXCCDvF2FegshLDU2",
        "1iSthZt2SDsWS3ELSjFkRsikVNtWDT1GmYzvPQQ"
    },
    {
        {0x00, 0x28, 0x7a, 0x57, 0xcd, 0xbe, 0x7b, 0x5c, 0xf8, 0x0f, 0x76,
         0x30, 0x9b, 0x29, 0x75, 0x6d, 0x25, 0x86, 0x60, 0x07, 0x2b, 0x30,
         0xda, 0x67, 0x7b},
        "14h2bDLZSuvRFhUL45VjPHJcW667mmRAAn",
        "1R9XA3AmWSAkSF6krDfnDmLjMQbtuz7ED7jDMbt"
    }
};


int main(int argc, char const *argv[]) {
    for (const auto& ex : examples) {
        // addresses should be equal
        std::cout << ex.string << std::endl;
        const auto encd  = crypto::base58_encode(ex.buffer);
        std::cout << encd << std::endl;
    }

    return 0;
}
