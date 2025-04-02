#include "levelManager.h"
#include "levelLoader/levelLoader.h"

LevelManager::LevelManager()
    : ILoadManager(new LevelLoader())
{}

void LevelManager::setDirectoryAndData(const QDir& dir, std::shared_ptr<LevelData> loadedData)
{
    m_levelDir = dir;
    m_loadedData = loadedData;
}

std::pair<size_t, size_t> LevelManager::getNonogramSize()
{
    if (m_loadedData && m_loadedData->isLoadedDataInformation)
    {
        return { m_loadedData->rowCount, m_loadedData->columnCount };
    }

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + infoDataFile;
    fileLoader->setFile(fullpath.toStdString());
    std::pair<size_t, size_t> sizes = fileLoader->getNonogramSize();

    if (m_loadedData)
    {
        m_loadedData->rowCount = sizes.first;
        m_loadedData->columnCount = sizes.second;
    }
    return sizes;
}

std::vector<std::array<size_t, 3>> LevelManager::getAdditionalCondition()
{
    if (m_loadedData->isLoadedDataInformation)
    {
        return m_loadedData->additionConditions;
    }

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + additionDataFile;
    fileLoader->setFile(fullpath.toStdString());
    std::vector<std::array<size_t, 3>> additionInfo = fileLoader->getAdditionalCondition();

    m_loadedData->additionConditions = additionInfo;
    return additionInfo;
}

std::vector<size_t> LevelManager::getLineSequence(bool isColumn, size_t lineIndex)
{
    if (m_loadedData->isLoadedDataInformation)
    {
        if (isColumn)
        {
            return m_loadedData->columnConditions[lineIndex];
        }

        return m_loadedData->lineConditions[lineIndex];
    }

    std::string fullpath = (m_levelDir.absolutePath() + "/" + conditionDataFile).toStdString();
    if (fileLoader->getFileName() != fullpath)
    {
        fileLoader->setFile(fullpath);
    }
    std::vector<size_t> condition = fileLoader->getLineSequence(isColumn, lineIndex);

    if (isColumn)
    {
        m_loadedData->columnConditions[lineIndex] = condition;
    }
    else
    {
        m_loadedData->lineConditions[lineIndex] = condition;
    }

    return condition;
}
