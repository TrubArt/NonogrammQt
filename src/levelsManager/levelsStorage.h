#ifndef LEVELSSTORAGE_H
#define LEVELSSTORAGE_H

#include <QDir>
#include <QList>
#include <QVarLengthArray>
#include <QMap>
#include <optional>

#include "colorstore.h"
#include "levelsDirectory.h"
#include "levelManager.h"

struct LevelData
{
    // data

    QVarLengthArray<QList<size_t>, 2> conditions;
    QList<QVarLengthArray<size_t, 3>> additionConditions;

    // properties

    int rowCount;
    int columnCount;
    QString name;
    ColorStore colors;
};


//**********************************************************//
//                       LevelsStorage                      //
//**********************************************************//


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
    LevelsDirectory m_levelsDir;

    QMap<levelname_al, LevelData> m_data;

    LevelManager m_manager;
};

#endif // LEVELSSTORAGE_H
