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

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + infoDataFile;
    fileLoader->setFile(fullpath.toStdString());
    return fileLoader->getNonogramSize();
}

std::vector<std::array<size_t, 3>> LevelManager::getAdditionalCondition()
{
    if (m_loadedData)
    {
        return m_loadedData->additionConditions;
    }

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + additionDataFile;
    fileLoader->setFile(fullpath.toStdString());
    return fileLoader->getAdditionalCondition();
}

std::vector<size_t> LevelManager::getLineSequence(bool isColumn, size_t lineIndex)
{
    if (m_loadedData)
    {
        if (isColumn)
        {
            return m_loadedData->columnConditions[lineIndex];
        }
        else
        {
            return m_loadedData->lineConditions[lineIndex];
        }
    }

    std::string fullpath = (m_levelDir.absolutePath() + "/" + conditionDataFile).toStdString();
    if (fileLoader->getFileName() != fullpath)
    {
        fileLoader->setFile(fullpath);
    }

    return fileLoader->getLineSequence(isColumn, lineIndex);
}
