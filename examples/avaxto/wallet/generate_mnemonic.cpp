#include <iostream>
#include <cstdlib>
#include <string>
#include <boost/program_options.hpp>

#include "avaxto/wallet/mnemonic.h"


/*
    Generate new mnemonic

    Optional parameter to count how many phrases to generate.
*/

namespace po = boost::program_options;


int main(int argc, char const *argv[]){
    const auto iov = po::invalid_option_value("value must be non-negative");

    int how_many = 1;
    if (argc > 1) {
        how_many = std::stoi(argv[1]);
    }

    for (int i=0;i<how_many;i++)
        std::cout << avaxto::wallet::new_mnemonic() << std::endl; 

    return 0;
}