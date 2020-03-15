cmake_minimum_required(VERSION 3.12.1)

set( PROJECT_NAME line-counter )
project( ${PROJECT_NAME} )

add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address" )
set( FLAGS -std=c++17 -Wall -g3 -fno-omit-frame-pointer -Wextra -Werror)

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googlemock/include")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googletest/include")

add_subdirectory(src)
