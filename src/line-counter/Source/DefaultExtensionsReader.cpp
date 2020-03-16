#include "DefaultExtensionsReader.h"

#include <iostream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

namespace lineCounter
{

DefaultExtensionsReader::DefaultExtensionsReader(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

FileExtensions DefaultExtensionsReader::readExtensions(const std::string& filePath) const
{
    if (const auto fileContent = readFileContainingExtensions(filePath))
    {
        return utils::getNonEmptyLines(utils::getSplitLines(*fileContent));
    }
    return {};
}

boost::optional<std::string>
DefaultExtensionsReader::readFileContainingExtensions(const std::string& filePath) const
{
    try
    {
        return fileAccess->readContent(filePath);
    }
    catch (const utils::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while reading extensions:" << e.what();
        return boost::none;
    }
}

}