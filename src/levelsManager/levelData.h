#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QList>
#include <QVarLengthArray>

#include "colorstore.h"

struct DataInformation
{
private:
    using conditionLine = std::vector<size_t>;
    using additionCondLine = std::array<size_t, 3>;

public:
    std::vector<conditionLine> lineConditions;
    std::vector<conditionLine> columnConditions;
    std::vector<additionCondLine> additionConditions;
};

struct PropertiesInformation
{
    int rowCount;
    int columnCount;
    QString name;
    ColorStore colors;
};

struct LevelData
{
    bool isLoadedDataInformation = false;
    DataInformation data;
    PropertiesInformation properties;
};

#endif // LEVELDATA_H
