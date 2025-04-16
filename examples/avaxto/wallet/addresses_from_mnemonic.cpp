#include <iostream>
#include <cstdlib>
#include <string>
#include <format>
#include "avaxto/wallet/mnemonic.h"
#include "avaxto/wallet/mnemonic_wallet.hpp"

/*        
    Take a mnemonic string as input, generate N addresses

    Usage: add_f_m <address_count> <12 or 24 words ...>

    NOTE: For demonstration purposes only. Do not use in production, as your mnemonic string will
    be stored in the shell history file and can be accessed by system administrators.


*/

int main(int argc, char const *argv[]) {

    int num_addrs = 1;

    if (argc < 14) {
        std::cerr << std::format("Usage: %s <number_addrs> < ... words>", argv[0]) << std::endl;
        return 1;
    }

    if (argc > 1) {
        num_addrs = std::stoi(argv[1]);
    }
    std::string mnemonic = "";
    for (int i=2;i<argc;i++) {
        mnemonic += std::string(argv[i]) + " ";
    }
    mnemonic = mnemonic.substr(0, mnemonic.length() - 1); // remove last space
    
    avaxto::wallet::mnemonic_wallet wallet{mnemonic, 0};

    // Print X-chain addresses
    std::cout << "X-Chain Addresses:" << std::endl;
    std::cout << std::setfill('-') << std::setw(80) << "-" << std::endl;
    for (uint32_t i = 0; i < 10; ++i) {
        std::cout << "Index " << i << ": " << wallet.derive_x_chain_address(i) << std::endl;
    }
    std::cout << std::endl;
    
    // Print P-chain addresses
    std::cout << "P-Chain Addresses:" << std::endl;
    std::cout << std::setfill('-') << std::setw(80) << "-" << std::endl;
    for (uint32_t i = 0; i < 10; ++i) {
        std::cout << "Index " << i << ": " << wallet.derive_p_chain_address(i) << std::endl;
    }
    
    std::cout << std::endl;
    
    // Print C-chain address
    std::cout << "C-Chain Address:" << std::endl;
    std::cout << std::setfill('-') << std::setw(80) << "-" << std::endl;    
    std::cout << wallet.derive_c_chain_address(0) << std::endl;
    
    std::cout << std::endl;
    std::cout << "*** WARNING!!!" << std::endl;
    std::cout << "*** Do NOT use these addresses. You WILL lose your coins. This is a work in progress. Address derivation is still being developed and is yet to be tested for correctness." << std::endl;
    std::cout << std::endl;

    return 0;
}