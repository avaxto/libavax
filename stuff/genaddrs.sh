#!/bin/bash
# This script generates a list of addresses from a mnemonic phrase using the avax wallet tool.
# It takes a mnemonic phrase and a number of addresses to generate as arguments.
# Usage: ./genaddrs.sh <number_of_addresses> <mnemonic_phrase>

cd "$(dirname "$0")/.."

OS_NAME=linux
if [[ $(uname -s) == "Darwin" ]]; then
    OS_NAME="mac"
fi

. ./scripts/setenv.sh

./build/$OS_NAME/examples/avaxto/wallet/addresses_from_mnemonic 10 `cat ./stuff/mnemonic.txt` 