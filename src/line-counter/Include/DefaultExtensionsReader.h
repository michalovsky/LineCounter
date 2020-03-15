#pragma once

#include "ExtensionsReader.h"
#include <memory>
#include "utils/FileAccess.h"
#include "boost/optional.hpp"

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