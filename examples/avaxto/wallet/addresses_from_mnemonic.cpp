#include <iostream>
#include <cstdlib>
#include "avaxto/wallet/mnemonic.h"
#include <string>
#include <format>

/*    
    
    Take a mnemonic string as input, generate N addresses

    Usage: add_f_m <number_addrs> < ... words>
*/

int main(int argc, char const *argv[]){

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
    std::cout << "Mnemonic: " << mnemonic << std::endl;
    std::cout << "Number of addresses: " << num_addrs << std::endl;
    
    return 0;
}