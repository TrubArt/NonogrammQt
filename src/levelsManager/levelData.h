#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QList>
#include <QVarLengthArray>
#include <memory>

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

    static DataInformation::conditionLine createConditionFromStr(const QString& line, std::shared_ptr<bool> hasCriticalError = nullptr);

    static QString createStrFromCondition(const DataInformation::conditionLine& lineData);
    static QString createStrFromAddition(const DataInformation::additionCondLine& lineData);
};

#endif // LEVELDATA_H
