#include "checker.h"
#include <QDebug>


bool Checker::checkDataValidation(Categories category, const QString& specialization, const QStringList& parameters)
{
    for (const QString& value : parameters)
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
            //-------------------------
        }
        else
        {
            Q_ASSERT_X(false, "LevelLoader::Checker::checkData" , "Unresolved category");
        }

        if (!goodValue)
        {
            messageFindBadParameter(specialization, value);
            return false;
        }
    }

    return true;
}

bool Checker::isOneSettingsInLine(const QStringList& parameters)
{
    return parameters.size() == 1 ? true : false;
}

bool Checker::isGoodAdditionalLine(const QStringList& parameters)
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

void Checker::messageFindBadParameter(const QString& specialization, const QString& value)
{
    qCritical() << "Bad values!"
                << " Parameter: " << specialization
                << " Value: " << value;
}
