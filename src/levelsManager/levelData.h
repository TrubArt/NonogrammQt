#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QList>
#include <QVarLengthArray>

#include "colorstore.h"

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

#endif // LEVELDATA_H
