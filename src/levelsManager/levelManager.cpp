#include "levelManager.h"

LevelManager::LevelManager()
{}

void LevelManager::loadLevels()
{
    auto list = m_dir.levelsList();
    for (const auto& i : list)
    {
        qDebug() << i;
    }
}

const LevelsDirectory& LevelManager::getLevelsDirectory() const
{
    return m_dir;
}

const LevelData* LevelManager::getLevelData(const QString& levelName) const
{
    for (const LevelLoader& level : m_levels)
    {
        if (level.getData().name == levelName)
        {
            return &level.getData();
        }
    }

    return nullptr;
}
