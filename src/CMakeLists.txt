add_library(libavax
    avaxto/wallet/mnemonic.cpp
)

target_link_libraries(libavax
    boost_system
    ssl
    crypto  
    bitcoin-system
)