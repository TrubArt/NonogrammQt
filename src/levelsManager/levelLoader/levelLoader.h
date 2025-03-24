#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <QFile>

#include "filesWork/iFileLoader.h"

class LevelLoader : public iFileLoader
{
public:
    LevelLoader() = default;

    void setFile(const std::string& fileName) override;
    std::string getFileName() const override;

    std::pair<size_t, size_t> getNonogramSize() override;
    std::vector<std::array<size_t, 3>> getAdditionalCondition() override;
    std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) override;

private:
    QFile m_file;

    enum class Categories
    {
        levelData,
        size,
        color
    };

    struct Checker
    {
        static bool checkDataValidation(Categories category, const QString& specialization, const QStringList& parameters);
        static bool isOneSettingsInLine(const QStringList& parameters);
        static bool checkSize(const QString& value);
    };
};

#endif // LEVELLOADER_H
