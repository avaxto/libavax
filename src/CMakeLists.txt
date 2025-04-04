add_library(libavax
    avaxto/wallet/mnemonic.cpp
    avaxto/crypto/cb58.cpp
    avaxto/crypto/randnr.cpp
    avaxto/utils/funcs.cpp
)

target_link_libraries(libavax
    PUBLIC
    bitcoin-system
    boost_system
    boost_program_options
    boost_regex
    ssl
    crypto      
)