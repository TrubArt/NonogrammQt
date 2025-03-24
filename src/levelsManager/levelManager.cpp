#include "levelManager.h"
#include "levelLoader/levelLoader.h"

LevelManager::LevelManager()
    : ILoadManager(new LevelLoader())
{}

void LevelManager::setDirectoryAndData(const QDir& dir, const std::optional<LevelData>& loadedData)
{
    m_levelDir = dir;
    m_loadedData = loadedData;
}

std::pair<size_t, size_t> LevelManager::getNonogramSize()
{
    if (m_loadedData)
    {
        return { m_loadedData->rowCount, m_loadedData->columnCount };
    }

    fileLoader->setFile(infoDataFile);
    return fileLoader->getNonogramSize();
}

std::vector<std::array<size_t, 3>> LevelManager::getAdditionalCondition()
{
    if (m_loadedData)
    {
        return m_loadedData->additionConditions;
    }

    fileLoader->setFile(additionDataFile);
    return fileLoader->getAdditionalCondition();
}

std::vector<size_t> LevelManager::getLineSequence(bool isColumn, size_t lineIndex)
{
    if (m_loadedData)
    {
        return m_loadedData->conditions[!isColumn][lineIndex];
    }

    if (fileLoader->getFileName() != conditionDataFile)
    {
        fileLoader->setFile(conditionDataFile);
    }
    return fileLoader->getLineSequence(isColumn, lineIndex);
}
