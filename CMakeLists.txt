cmake_minimum_required(VERSION 3.12.1)

set( PROJECT_NAME line-counter )
project( ${PROJECT_NAME} )

add_subdirectory(externals)

set(CMAKE_CXX_STANDARD 20)
if(MSVC)
    set(FLAGS /std:c++latest /permissive-)
else()
    set(FLAGS -std=c++20 -Wall -g3 -fno-omit-frame-pointer -Wextra -Werror)
endif()

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googlemock/include")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals/googletest/googletest/include")

add_subdirectory(src)
