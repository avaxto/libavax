# libavax

C++ Avalanche / AVAX library

`libavax` is an experimental C and C++ AVAX library

Running on linux only at this time. Mac development is slowly ongoing but there are still build issues.


# Build

You'll need the standard GNU C++ build tools for your distro

On Ubuntu/Debian distros, this should cover it:

`sudo apt-get install build-essential autoconf automake libtool pkg-config git`

## Dependencies

* [libbitcoin-system](https://github.com/libbitcoin/libbitcoin-system) v3.8.0 or higher


## Build instructions

libavax uses the cmake build generator

In the project source dir, run:

```
mkdir build
cmake -B . -S ./build
cmake --build ./build

# optional step for systemwide install
sudo cmake --install 
```

Binaries will be found under `./build` 

To clean up and start a new build, just remove the `./build` directory. Everything in it is recreated by the build system and can be discarded. 

NOTE: Never save any valuable data in `./build`

# Getting Started

See the `examples/` folder for sample code and utils built using `libavax`


# Help

Priority support is provided via [rektbuildr](https://arena.social/rektbuildr) and [avaxto](https://arena.social/avaxto) Arena App Private Chat

Note: @rektbuildr or @avaxto ticket purchase required to access Arena Private Chat

## Github Issue Tracker

For technical / source code questions please [open a Github ticket](https://github.com/rektbuildr/libavax/issues).


Note: Github tickets strictly meant for source code issues, bug reports, and code improvement requests. Please provide a source code reference file(s). Include line numbers when possible.

## Social Media

Feedback and comments always welcome ♥️ !

[@avaxto Twitter](https://twitter.com/avaxto)

[@REKTBuildr Twitter](https://twitter.com/rektbuildr)

[@avaxto Telegram](https://t.me/avaxto)

Note: if your support request hasn't been replied to yet, please ping us at one of our social channels above.

# License

libavax is licensed under the GPL. See LICENSE file.
