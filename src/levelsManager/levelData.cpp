#include "levelData.h"

#include "levelLoader/checker.h"
#include "levelLoader/fileParser.h"

#include <QDebug>

DataInformation::conditionLine LevelData::createConditionFromStr(const QString& line, std::shared_ptr<bool> hasCriticalError)
{
    DataInformation::conditionLine condition;

    QStringList values;
    FileParser::getLevelData(line, values);
    FileParser::deleteNulls(values);

    condition.reserve(values.size());
    for (const QString& value : std::as_const(values))
    {
        if (hasCriticalError && !Checker::checkDataValidation(Checker::Categories::levelData, value))
        {
            *hasCriticalError = true;
            // TODO: добавить логер, который будет содержать эти записи

            // qCritical() << "Bad values!"
            //             << " Parameter: " << "level data value"
            //             << " Value: " << value;
        }
        else
        {
            condition.push_back(value.toInt());
        }
    }

    if (condition.empty())
    {
        // TODO: добавить логер, который будет содержать эти записи

        // qWarning() << "Not find condition to" << " "
        //             << (isColumn ? "column" : "line") << " "
        //             << "condition number: " << lineIndex;

        condition.push_back(0);
    }

    return condition;
}

QString LevelData::createStrFromCondition(const DataInformation::conditionLine& lineData)
{
    QString data;
    int size = lineData.size();
    data.reserve(size * 3); // *3 из расчёта что одно число оптимально двузначное + пробелы между каждым числом
    for (int i = 0; i < size; ++i)
    {
        if (i != 0)
        {
            data += " ";
        }
        data += QString::number(lineData[i]);
    }
    return data;
}

QString LevelData::createStrFromAddition(const DataInformation::additionCondLine& lineData)
{
    QString line;
    line.reserve(7); // 7 из расчёта что размер нонограммы (двузначное число оптимально + 2 пробела) + 1 на цвет
    line += QString::number(lineData[0]) + " ";
    line += QString::number(lineData[1]) + " ";
    line += QString::number(lineData[2]);
    return line;
}
