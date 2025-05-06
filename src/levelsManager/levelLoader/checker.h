#ifndef CHECKER_H
#define CHECKER_H

#include <QList>

class Checker
{
public:
    enum class Categories
    {
        levelData,
        additionData,
        size,
        color
    };

    static bool checkDataValidation(Categories category, const QString& value);

    // count values check

    static bool is1SettingsInLine(const QStringList& parameters);
    static bool is3ParametresInAdditionalLine(const QStringList& parameters);

    // special check for categories

    static bool checkSize(const QString& value);
    static bool checkData(const QString& value);
    static bool checkColor(const QString& value);
};

#endif // CHECKER_H
