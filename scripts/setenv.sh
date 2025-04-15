#!/usr/bin/env bash

# include this file into the current shell
# by running
# . ./scripts/setenv.sh


export AVAXTO_HOME="$(dirname "$0")/.."
# for Macos
export DYLD_LIBRARY_PATH=~/libbitcoin-build/lib:$DYLD_LIBRARY_PATH

