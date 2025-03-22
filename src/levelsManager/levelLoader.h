#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <QDir>
#include <QList>
#include <QVarLengthArray>

#include "filesWork/iLoadManager.h"
#include "colorstore.h"

struct LevelData
{
    // data

    QVarLengthArray<QList<size_t>, 2> conditions;
    QList<QList<size_t>> additionConditions;
    int rowCount;
    int columnCount;

    // properties

    QString name;
    ColorStore colors;
};

//**********************************************************//
//                       LevelLoader                        //
//**********************************************************//

class LevelLoader : public ILoadManager
{
public:
    LevelLoader(QDir levelDirectory);

    std::pair<size_t, size_t> getNonogramSize() override;
    std::vector<std::array<size_t, 3>> getAdditionalCondition() override;
    std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) override;

    const LevelData& getData() const;
    LevelData& getData();

private:
    LevelData m_levelData;
};

#endif // LEVELLOADER_H
