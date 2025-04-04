add_library(avax
    avaxto/wallet/mnemonic.cpp
    avaxto/crypto/cb58.cpp
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