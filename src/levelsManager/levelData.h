#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QList>
#include <QVarLengthArray>

#include "colorstore.h"

struct DataInformation
{
    using conditionLine = std::vector<size_t>;
    using additionCondLine = std::array<size_t, 3>;

    std::vector<conditionLine> lineConditions;
    std::vector<conditionLine> columnConditions;
    std::vector<additionCondLine> additionConditions;
};

struct PropertiesInformation
{
    int rowCount;
    int columnCount;
    ColorStore colors;
};

struct LevelData
{
    bool isLoadedDataInformation = false;
    DataInformation data;
    PropertiesInformation properties;

    static QString createConditionStrLine(const DataInformation::conditionLine& lineData);
    static QString createAdditionStrLine(const DataInformation::additionCondLine& lineData);
};

#endif // LEVELDATA_H
