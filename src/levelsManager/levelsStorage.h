#ifndef LEVELSSTORAGE_H
#define LEVELSSTORAGE_H

#include <QMap>
#include <memory>

#include "levelsDirectory.h"
#include "levelManager.h"

class LevelsStorage
{
    using levelname_al = QString;

public:
    using dataType = QMap<levelname_al, std::shared_ptr<LevelData>>;
    LevelsStorage() = default;

    void loadLevels();
    void setProperties(const QString& levelName, const PropertiesInformation& newProperties);
    void saveSettings();

    void addLevel(const QString& levelName, std::shared_ptr<LevelData> level);
    void deleteLevel(const QString& levelName);  // undef

    QList<levelname_al> getLevelsList() const;
    dataType& getData();
    const dataType& getData() const;
    std::shared_ptr<LevelData> getLevelData(const QString& levelName) const;
    LevelManager& getManager(const QString& levelName);

private:
    LevelData loadLevelSettingsWithoutData(const QString& levelName);
    void setDirectoryAndData(const QString& levelName, std::shared_ptr<LevelData> loadedData);

    LevelsDirectory m_levelsDir;
    dataType m_data;
    LevelManager m_manager;
};

#endif // LEVELSSTORAGE_H
