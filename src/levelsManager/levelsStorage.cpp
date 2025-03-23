#include "levelsStorage.h"
#include "levelLoader.h"

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
    // настройка нужного менеджера по заданному levelName
    return m_manager;
}
