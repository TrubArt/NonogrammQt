#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QList>

class FileParser
{
public:
    FileParser() = default;
    static void getSettingsData(const QString& line, QString& category, QStringList& parameters);
    static void getLevelData(const QString& line, QStringList& parameters);
    static void deleteBadSymbols(QString& parametr);

private:
    static const QString m_separatorForSettings;
    static const QStringList m_ignoredValues;
};

#endif // FILEPARSER_H
