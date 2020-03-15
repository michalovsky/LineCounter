#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "ExtensionsReader.h"
#include "utils/FileAccess.h"

namespace lineCounter
{

class DefaultExtensionsReader : public ExtensionsReader
{
public:
    DefaultExtensionsReader(std::shared_ptr<utils::FileAccess>);

    FileExtensions readExtensions(const std::string& filePath) const override;

private:
    boost::optional<std::string> readFileContainingExtensions(const std::string& filePath) const;

    std::shared_ptr<utils::FileAccess> fileAccess;
};
}