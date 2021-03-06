set(SOURCES
        src/DefaultFileAccess.cpp
        src/ProjectFileAccess.cpp
        src/StringHelper.cpp
        src/GetProjectPath.cpp
        src/GetExecutablePath.cpp
        src/FileAccessFactory.cpp
        src/FileAccessFactoryImpl.cpp
        src/FileExtensionsFilter.cpp
        src/FilenamePathFilter.cpp
        )

set(UT_SOURCES
        src/DefaultFileAccessTest.cpp
        src/ProjectFileAccessTest.cpp
        src/StringHelperTest.cpp
        src/GetExecutablePathTest.cpp
        src/GetProjectPathTest.cpp
        src/FileExtensionFilterTest.cpp
        src/FilenamePathFilterTest.cpp
        )


add_library(utils ${SOURCES})
add_executable(utilsUT ${UT_SOURCES})

target_include_directories(utils PUBLIC "include" PRIVATE "include/utils" ${Boost_INCLUDE_DIR})
target_include_directories(utilsUT PRIVATE "include" "include/utils" ${Boost_INCLUDE_DIR})

target_link_libraries(utilsUT PRIVATE gtest_main gmock utils)

target_compile_options(utils PUBLIC ${FLAGS})
target_compile_options(utilsUT PUBLIC ${FLAGS})

add_test(utilsUT utilsUT --gtest_color=yes)
