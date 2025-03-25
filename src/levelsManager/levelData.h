#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QList>
#include <QVarLengthArray>

#include "colorstore.h"

struct LevelData
{
private:
    using conditionLine = std::vector<size_t>;
    using additionCondLine = std::array<size_t, 3>;

public:

    // data

    std::vector<conditionLine> lineConditions;
    std::vector<conditionLine> columnConditions;
    std::vector<additionCondLine> additionConditions;

    // properties

    int rowCount;
    int columnCount;
    QString name;
    ColorStore colors;
};

#endif // LEVELDATA_H
