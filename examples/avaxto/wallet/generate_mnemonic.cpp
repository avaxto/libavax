#include <iostream>
#include <cstdlib>
#include <string>
#include "avaxto/wallet/mnemonic.h"


/*
    Generate new mnemonic

    Optional parameter to count how many phrases to generate.
*/

int main(int argc, char const *argv[]){

    int how_many = 1;
    if (argc > 1) {
        how_many = std::stoi(argv[1]);
    }

    for (int i=0;i<how_many;i++)
        std::cout << avaxto::wallet::new_mnemonic() << std::endl; 

    return 0;
}