#include "levelsStorage.h"

void LevelsStorage::loadLevels()
{
    QStringList listLevelsName = m_levelsDir.levelsList();
    for (const QString& levelName : listLevelsName)
    {
        m_data[levelName] = std::make_shared<LevelData>(loadLevelSettingsWithoutData(levelName));
    }
}

QList<LevelsStorage::levelname_al> LevelsStorage::getLevelsList() const
{
    return m_data.keys();
}

LevelsStorage::dataType& LevelsStorage::getData()
{
    return m_data;
}

const LevelsStorage::dataType& LevelsStorage::getData() const
{
    return m_data;
}

std::shared_ptr<LevelData> LevelsStorage::getLevelData(const QString& levelName) const
{
    if (m_data.find(levelName) != m_data.end())
    {
        return m_data[levelName];
    }

    return nullptr;
}

LevelManager& LevelsStorage::getManager(const QString& levelName)
{
    setDirectoryAndData(levelName, getLevelData(levelName));
    return m_manager;
}

LevelData LevelsStorage::loadLevelSettingsWithoutData(const QString& levelName)
{
    setDirectoryAndData(levelName, nullptr);
    LevelData data_t;

    std::pair<size_t, size_t> sizes = m_manager.getNonogramSize();
    data_t.lineConditions.resize(sizes.first);
    data_t.columnConditions.resize(sizes.second);

    data_t.rowCount = sizes.first;
    data_t.columnCount = sizes.second;
    data_t.name = levelName;

    return data_t;
}

void LevelsStorage::setDirectoryAndData(const QString& levelName, std::shared_ptr<LevelData> loadedData)
{
    m_manager.setDirectoryAndData(QDir(m_levelsDir.getAbsPath(levelName)), loadedData);
}
