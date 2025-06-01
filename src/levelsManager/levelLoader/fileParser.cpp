#include "fileParser.h"

#include <QDebug>
#include <memory>

const QString FileParser::m_separatorForSettings = ":";
const QStringList FileParser::m_ignoredValues = { "\t", "\r", "\n" };

void FileParser::getSettingsData(const QString& line, QString& category, QStringList& parameters)
{
    QStringList listBySplit = line.split(m_separatorForSettings);
    if (listBySplit.size() == 1)
    {
        qCritical() << "Absent '" << m_separatorForSettings << "' in line" << line;
        return;
    }
    if (listBySplit.size() > 2)
    {
        qCritical() << "To much '" << m_separatorForSettings << "' in line" << line;
        return;
    }

    category = listBySplit[0];

    getLevelData(listBySplit[1], parameters);
}

void FileParser::getLevelData(const QString& line, QStringList& parameters)
{
    QStringList listParametres = line.split(" ");
    if (listParametres.size() > listParametres.capacity())
    {
        parameters.reserve(listParametres.size());
    }

    for (QString& value : listParametres)
    {
        deleteBadSymbols(value);
        if (!value.isEmpty())
        {
            parameters.push_back(value);
        }
    }
}

void FileParser::deleteBadSymbols(QString& parametr)
{
    for (const QString& value : m_ignoredValues)
    {
        qsizetype indexValue = parametr.indexOf(value);
        while (indexValue != -1)
        {
            parametr.remove(indexValue, value.size());
            indexValue = parametr.indexOf(value);
        }
    }
}

void FileParser::deleteNulls(QStringList& condition)
{
    int size = condition.size();
    for (int i = 0; i < size;)
    {
        QString elem = condition[i];
        std::unique_ptr<bool> checkToConversion = std::make_unique<bool>(true);
        int value = elem.toInt(checkToConversion.get());
        if (*checkToConversion == false || value != 0)
        {
            ++i;
            continue;
        }

        if (size == 1)  // если ноль всего 1, не удаляем, тк условие не должно быть пустым
        {
            return;
        }

        condition.removeAt(i);
        size -= 1;
    }
}
