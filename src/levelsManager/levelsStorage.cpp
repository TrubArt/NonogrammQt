#include "levelsStorage.h"

void LevelsStorage::loadLevels()
{
    QStringList listLevelsName = m_levelsDir.levelsList();
    for (const QString& levelName : listLevelsName)
    {
        LevelData loadedData;
        m_data[levelName] = loadedData;
    }
}

QList<LevelsStorage::levelname_al> LevelsStorage::getLevelsList() const
{
    return m_data.keys();
}

std::optional<LevelData> LevelsStorage::getLevelData(const QString& levelName) const
{
    if (m_data.find(levelName) != m_data.end())
    {
        return m_data[levelName];
    }

    return std::nullopt;
}

LevelManager& LevelsStorage::getManager(const QString& levelName)
{
    QString levelDirectoryName = m_levelsDir.path() + QDir::separator() + levelName;
    m_manager.setDirectoryAndData(QDir(levelDirectoryName), isLoadedData(levelName));
    return m_manager;
}

std::optional<LevelData> LevelsStorage::isLoadedData(const QString& levelName) const
{
    std::optional<LevelData> existLevel = getLevelData(levelName);
    if (existLevel == std::nullopt || existLevel->conditions.empty())
    {
        return std::nullopt;
    }

    return existLevel;
}
