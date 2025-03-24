#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QList>

class FileParser
{
public:
    FileParser() = default;
    static void getSettingsData(const QString& line, QString& category, QStringList& parameters);
    static void getLevelData(const QString& line, QStringList& parameters);

private:

};

#endif // FILEPARSER_H
