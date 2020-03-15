
set(SOURCES
        Source/LineCounter.cpp
        Source/DefaultExtensionsReader.cpp
        Source/DefaultPathsToIgnoreReader.cpp
        Source/RecursiveFilePathsFinder.cpp
        Source/DefaultFilePathsSelector.cpp
        )

set(UT_SOURCES
        UT/Source/LineCounterTest.cpp
        UT/Source/DefaultExtensionsReaderTest.cpp
        UT/Source/DefaultPathsToIgnoreReaderTest.cpp
        UT/Source/RecursiveFilePathsFinderTest.cpp
        UT/Source/DefaultFilePathsSelectorTest.cpp
        )

add_executable(line-counter ${SOURCES} Source/Main.cpp)
add_executable(line-counterUT ${UT_SOURCES} ${SOURCES})

target_include_directories(line-counter PUBLIC "Include" PRIVATE)
target_include_directories(line-counterUT PUBLIC "Include" "UT/Doubles" "UT/")

target_link_libraries(line-counter PUBLIC ${Boost_LIBRARIES} utils)
target_link_libraries(line-counterUT PUBLIC gtest_main gmock pthread utils)

target_compile_options(line-counter PUBLIC ${FLAGS})
target_compile_options(line-counterUT PUBLIC -Wall -Wextra -Werror)

add_test(line-counterUT line-counterUT --gtest_color=yes)