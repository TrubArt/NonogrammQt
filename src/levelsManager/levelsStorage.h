#ifndef LEVELSSTORAGE_H
#define LEVELSSTORAGE_H

#include <QMap>

#include "levelsDirectory.h"
#include "levelManager.h"

class LevelsStorage
{
    using levelname_al = QString;

public:
    LevelsStorage() = default;

    void loadLevels();
    QList<levelname_al> getLevelsList() const;
    std::optional<LevelData> getLevelData(const QString& levelName) const;
    LevelManager& getManager(const QString& levelName);

private:
    std::optional<LevelData> isLoadedData(const QString& levelName) const;
    LevelData loadLevelSettingsWithoutData(const QString& levelName);
    void setDirectoryAndData(const QString& levelName, const std::optional<LevelData>& loadedData);

    LevelsDirectory m_levelsDir;
    QMap<levelname_al, LevelData> m_data;
    LevelManager m_manager;
};

#endif // LEVELSSTORAGE_H
