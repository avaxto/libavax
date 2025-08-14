cmake_minimum_required(VERSION 3.28.3)

project(libavax)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_VERBOSE_MAKEFILE true)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

include(FetchContent)

# Check if LIBBITCOIN_PATH environment variable is set
# if(DEFINED ENV{LIBBITCOIN_PATH})
#     set(LIBBITCOIN_PATH $ENV{LIBBITCOIN_PATH})
#     message(STATUS "Using LIBBITCOIN_PATH from environment: ${LIBBITCOIN_PATH}")
# else()
#     # Get user's home directory
#     if(WIN32)
#         set(USER_HOME_DIR $ENV{USERPROFILE})
#     else()
#         set(USER_HOME_DIR $ENV{HOME})
#     endif()
#     set(LIBBITCOIN_PATH "${USER_HOME_DIR}/libbitcoin-build")
#     message(STATUS "LIBBITCOIN_PATH not set, using default: ${LIBBITCOIN_PATH}")
# endif()

# Set include and link directories for libbitcoin
# include_directories(${LIBBITCOIN_PATH}/include)
# link_directories(${LIBBITCOIN_PATH}/lib)

FetchContent_Declare(
nlohmann_json
GIT_REPOSITORY https://github.com/nlohmann/json
GIT_TAG  v3.11.3
GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(nlohmann_json)

# comment this out for deprecation warnings
add_compile_options(-Wno-deprecated-declarations -Wno-error -Wno-deprecated-builtins)

include_directories(include)
include_directories(/usr/local/include)
include_directories(${json_SOURCE_DIR}/include)


if(MACOSX)
    include_directories(/opt/homebrew/include)
    link_directories(/usr/local/lib)
    link_directories(/opt/homebrew/lib)
    #set(CMAKE_C_COMPILER "/opt/local/bin/gcc")
    #set(CMAKE_CXX_COMPILER "/opt/local/bin/g++")
endif()

add_subdirectory(src)
add_subdirectory(examples)


