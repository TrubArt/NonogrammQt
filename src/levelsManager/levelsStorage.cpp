#include "levelsStorage.h"
#include "../utils.h"

void LevelsStorage::loadLevels()
{
    const QStringList listLevelsName = m_levelsDir.levelsList();
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

void LevelsStorage::setProperties(const QString& levelName, const PropertiesInformation& newProperties)
{
    m_data[levelName]->properties = newProperties;
}

void LevelsStorage::saveSettings()
{
    for (auto it = m_data.begin(); it != m_data.end(); ++it)
    {
        QString levelName = it.key();
        std::shared_ptr<LevelData> data = it.value();
        setDirectoryAndData(levelName, data);
        m_manager.saveAll();
    }
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
    data_t.data.lineConditions.resize(sizes.first);
    data_t.data.columnConditions.resize(sizes.second);

    data_t.properties.rowCount = sizes.first;
    data_t.properties.columnCount = sizes.second;
    data_t.properties.colors = m_manager.getNonogramColors();

    return data_t;
}

void LevelsStorage::setDirectoryAndData(const QString& levelName, std::shared_ptr<LevelData> loadedData)
{
    m_manager.setDirectoryAndData(QDir(m_levelsDir.getAbsPath(levelName)), loadedData);
}

void LevelsStorage::addLevel(const QString& levelName, std::shared_ptr<LevelData> level)
{
    Q_ASSERT_X(!getLevelsList().contains(levelName), "LevelsStorage::addLevel", "level exist!");
    m_data[levelName] = level;
}

void LevelsStorage::deleteLevel(const QString& levelName)
{
    bool removed = m_data.remove(levelName);
    if (!removed)
    {
        Q_ASSERT_X(false, "LevelsStorage::deleteLevel", "level not exist!");
    }

    utils::deleteFullDirectory(m_levelsDir.getAbsPath(levelName));
}
