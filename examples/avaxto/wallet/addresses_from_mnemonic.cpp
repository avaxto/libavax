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
    
    if (argc < 14) {
        std::cerr << std::format("Usage: %s <number_addrs> < ... words>", argv[0]) << std::endl;
        return 1;
    }


    
    return 0;
}