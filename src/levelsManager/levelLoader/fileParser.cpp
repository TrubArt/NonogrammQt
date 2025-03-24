#include <QObject>

#include "fileParser.h"

void FileParser::getSettingsData(const QString& line, QString& category, QStringList& parameters)
{
    QStringList listBySplit = line.split(":");
    if (listBySplit.size() == 1)
    {
        qCritical() << QObject::tr("Absent ':' in line") << line;
        return;
    }
    if (listBySplit.size() > 2)
    {
        qCritical() << QObject::tr("To much ':' in line") << line;
        return;
    }

    category = listBySplit[0];

    getLevelData(listBySplit[1], parameters);
}

void FileParser::getLevelData(const QString& line, QStringList& parameters)
{
    QStringList listParametres = line.split(" ");
    parameters.reserve(listParametres.size());
    for (const QString& value : listParametres)
    {
        if (!value.isEmpty())
        {
            parameters.push_back(value);
        }
    }
}
