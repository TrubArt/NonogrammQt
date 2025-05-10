#include "levelData.h"

QString LevelData::createConditionStrLine(const DataInformation::conditionLine& lineData)
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

QString LevelData::createAdditionStrLine(const DataInformation::additionCondLine& lineData)
{
    QString line;
    line.reserve(9); // 9 из расчёта что размер нонограммы (трёхзначное число оптимально + 2 пробела) + 1 на цвет
    line += QString::number(lineData[0]) + " ";
    line += QString::number(lineData[1]) + " ";
    line += QString::number(lineData[2]);
    return line;
}
