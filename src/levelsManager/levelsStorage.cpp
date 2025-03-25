#include "levelsStorage.h"

void LevelsStorage::loadLevels()
{
    QStringList listLevelsName = m_levelsDir.levelsList();
    for (const QString& levelName : listLevelsName)
    {
        m_data[levelName] = loadLevelSettingsWithoutData(levelName);
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
    setDirectoryAndData(levelName, isLoadedData(levelName));
    return m_manager;
}

std::optional<LevelData> LevelsStorage::isLoadedData(const QString& levelName) const
{
    std::optional<LevelData> existLevel = getLevelData(levelName);
    if (existLevel == std::nullopt || existLevel->lineConditions.empty())
    {
        return std::nullopt;
    }

    return existLevel;
}

LevelData LevelsStorage::loadLevelSettingsWithoutData(const QString& levelName)
{
    setDirectoryAndData(levelName, std::nullopt);
    LevelData data_t;

    std::pair<size_t, size_t> sizes = m_manager.getNonogramSize();

    data_t.rowCount = sizes.first;
    data_t.columnCount = sizes.second;
    data_t.name = levelName;

    return data_t;
}

void LevelsStorage::setDirectoryAndData(const QString& levelName, const std::optional<LevelData>& loadedData)
{
    m_manager.setDirectoryAndData(QDir(m_levelsDir.getAbsPath(levelName)), loadedData);
}
