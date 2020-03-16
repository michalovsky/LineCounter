#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "PathsToIgnoreReader.h"
#include "utils/FileAccess.h"

namespace lineCounter
{
class DefaultPathsToIgnoreReader : public PathsToIgnoreReader
{
public:
    explicit DefaultPathsToIgnoreReader(std::shared_ptr<utils::FileAccess>);

    PathsToIgnore readPathsToIgnore(const std::string& filePath) const override;

private:
    boost::optional<std::string> readFileContainingIgnoredPaths(const std::string& filePath) const;
    PathsToIgnore selectExistingPaths(const PathsToIgnore&) const;

    std::shared_ptr<utils::FileAccess> fileAccess;
};
}