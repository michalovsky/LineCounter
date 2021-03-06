#include "GetProjectPath.h"

#include "boost/algorithm/string/predicate.hpp"
#include "gtest/gtest.h"

#include "exceptions/FileNotFound.h"

using namespace ::testing;
using namespace utils;

class GetProjectPathTest : public Test
{
public:
    const std::string validProjectName{"line-counter"};
    const std::string validPathEnd{"line-counter/"};
    const std::string invalidProjectName{"nasjxanxjqq"};
};

TEST_F(GetProjectPathTest, givenValidProjectName_shouldReturnProjectPath)
{
    const auto actualProjectPath = getProjectPath(validProjectName);

    ASSERT_TRUE(boost::algorithm::ends_with(actualProjectPath, validPathEnd));
}

TEST_F(GetProjectPathTest, givenInvalidProjectName_shouldThrowFileNotFound)
{
    ASSERT_THROW(getProjectPath(invalidProjectName), exceptions::FileNotFound);
}