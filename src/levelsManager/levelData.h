#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QList>
#include <QVarLengthArray>

#include "colorstore.h"

struct LevelData
{
    // data

    std::array<std::vector<size_t>, 2> conditions;
    std::vector<std::array<size_t, 3>> additionConditions;

    // properties

    int rowCount;
    int columnCount;
    QString name;
    ColorStore colors;
};

#endif // LEVELDATA_H
