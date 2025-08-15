add_library(avax STATIC   
    avaxto/crypto/bech32.cpp
    avaxto/crypto/cb58.cpp
    avaxto/crypto/keccak256.cpp
    avaxto/crypto/randnr.cpp
    avaxto/utils/funcs.cpp    
    avaxto/wallet/evm_wallet.cpp
    avaxto/wallet/hd_scanner.cpp
    avaxto/wallet/hd_wallet_abstract.cpp
    avaxto/wallet/mnemonic.cpp
    avaxto/wallet/mnemonic_wallet.cpp
    # Real BIP39 dictionary implementation
    libbitcoin/system/dictionary.cpp
    # Real libbitcoin-system implementations
    bitcoin/system/wallet/mnemonic.cpp
    bitcoin/system/wallet/hd_private.cpp
    bitcoin/system/wallet/hd_public.cpp
    bitcoin/system/wallet/encrypted_keys.cpp
    bitcoin/system/math/crypto.cpp
    # External AES256 implementation
    bitcoin/system/math/external/aes256.c
)

target_link_libraries(avax
    PUBLIC
    boost_system
    boost_regex
    ssl
    crypto      
    secp256k1
    gmp
    boost_program_options
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