#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QList>
#include <QDebug>

class FileParser
{
public:
    FileParser() = default;
    static void getSettingsData(const QString& line, QString& category, QStringList& parameters);
    static void getLevelData(const QString& line, QStringList& parameters);

private:
    static void deleteBadSymbols(QString& parametr);

    static const QString m_separatorForSettings;
    static const QStringList m_ignoredValues;
};

#endif // FILEPARSER_H
