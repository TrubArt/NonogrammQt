#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "levelsDirectory.h"
#include "levelLoader.h"

class LevelManager
{
public:
    LevelManager();

    void loadLevels();
    const LevelsDirectory& getLevelsDirectory() const;
    const LevelData* getLevelData(const QString& levelName) const;

private:
    LevelsDirectory m_dir;
    QList<LevelLoader> m_levels;
};

#endif // LEVELMANAGER_H
