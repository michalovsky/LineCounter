#include "LineCounterApplication.h"

#include "DefaultExtensionsReader.h"
#include "DefaultFilePathsSelector.h"
#include "DefaultPathsToIgnoreReader.h"
#include "RecursiveFilePathsFinder.h"
#include "utils/FileAccessFactory.h"

namespace lineCounter
{

LineCounterApplication::LineCounterApplication()
{
    initializeLineCounter();
}

long LineCounterApplication::getAmountOfLines(const ConfigFilePaths& configFilePaths) const
{
    return lineCounter->getAmountOfLines(configFilePaths);
}

void LineCounterApplication::initializeLineCounter()
{
    const auto fileAccessFactory = utils::FileAccessFactory::createFileAccessFactory();
    std::shared_ptr<utils::FileAccess> fileAccess = fileAccessFactory->createDefaultFileAccess();
    lineCounter = std::make_unique<LineCounter>(
        std::make_unique<DefaultFilePathsSelector>(std::make_unique<RecursiveFilePathsFinder>(fileAccess),
                                                   std::make_unique<DefaultPathsToIgnoreReader>(fileAccess),
                                                   std::make_unique<DefaultExtensionsReader>(fileAccess)),
        fileAccess);
}

}