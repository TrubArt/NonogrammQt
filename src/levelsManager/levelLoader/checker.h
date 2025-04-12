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

    Checker() = default;
    static bool checkDataValidation(Categories category, const QString& specialization, const QStringList& parameters);

    // count values check

    static bool isOneSettingsInLine(const QStringList& parameters);
    static bool isGoodAdditionalLine(const QStringList& parameters);

    // special check for categories

    static bool checkSize(const QString& value);
    static bool checkData(const QString& value);

private:
    static void messageFindBadParameter(const QString& specialization, const QString& value);
};

#endif // CHECKER_H
