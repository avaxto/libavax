add_library(avax
    avaxto/wallet/mnemonic.cpp
    avaxto/crypto/cb58.cpp
    avaxto/crypto/keccak256.cpp
    avaxto/crypto/randnr.cpp
    avaxto/utils/funcs.cpp
)

target_link_libraries(avax
    PUBLIC
    bitcoin-system
    boost_system
    boost_program_options
    boost_regex
    ssl
    crypto      
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