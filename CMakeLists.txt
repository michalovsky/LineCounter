cmake_minimum_required(VERSION 3.14)
set( PROJECT_NAME line-counter  )

project( ${PROJECT_NAME} )

set(CMAKE_CXX_STANDARD 17)

set( CMAKE_BUILD_TYPE Debug )

set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/Main.cpp
        ${CMAKE_SOURCE_DIR}/src/File.cpp
        ${CMAKE_SOURCE_DIR}/src/LineCounter.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "./include")

target_link_libraries(${PROJECT_NAME} stdc++fs)