#include "checker.h"
#include <QColor>


bool Checker::checkDataValidation(Categories category, const QString& value)
{
    bool goodValue = false;
    if (category == Categories::size)
    {
        goodValue = checkSize(value);
    }
    else if (category == Categories::levelData || category == Categories::additionData)
    {
        goodValue = checkData(value);
    }
    else if (category == Categories::color)
    {
        goodValue = checkColor(value);
    }
    else
    {
        Q_ASSERT_X(false, "LevelLoader::Checker::checkData" , "Unresolved category");
    }

    return goodValue;
}

bool Checker::is1SettingsInLine(const QStringList& parameters)
{
    return parameters.size() == 1 ? true : false;
}

bool Checker::is3ParametresInAdditionalLine(const QStringList& parameters)
{
    return parameters.size() == 3 ? true : false;
}

bool Checker::checkSize(const QString& str)
{
    std::unique_ptr<bool> checkToConversion = std::make_unique<bool>(true);
    int value = str.toInt(checkToConversion.get());
    if (*checkToConversion == false || value <= 0)
    {
        return false;
    }
    return true;
}

bool Checker::checkData(const QString& str)
{
    std::unique_ptr<bool> checkToConversion = std::make_unique<bool>(true);
    int value = str.toInt(checkToConversion.get());
    if (*checkToConversion == false || value < 0)
    {
        return false;
    }
    return true;
}

bool Checker::checkColor(const QString& str)
{
    return QColor::isValidColorName(str);
}
