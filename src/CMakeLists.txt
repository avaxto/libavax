add_library(avax    
    avaxto/crypto/cb58.cpp
    avaxto/crypto/keccak256.cpp
    avaxto/crypto/randnr.cpp
    avaxto/utils/funcs.cpp    
    avaxto/wallet/evm_wallet.cpp
    avaxto/wallet/hd_scanner.cpp
    avaxto/wallet/hd_wallet_abstract.cpp
    avaxto/wallet/mnemonic.cpp
    avaxto/wallet/mnemonic_wallet.cpp
)

target_link_libraries(avax
    PUBLIC
    bitcoin-system
    boost_system
    boost_program_options
    boost_regex
    ssl
    crypto      
    secp256k1
    gmp
)

# C language lib
add_library(avax-c
    avaxto/network/beacons.c
    avaxto/network/connect.c
    avaxto/network/fields.c
    avaxto/network/msg.c
    avaxto/network/network.c    
    avaxto/network/opcodes.c
    avaxto/network/peer.c
    
    
)