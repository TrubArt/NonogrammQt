#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <QFile>
#include <QVarLengthArray>
#include <QColor>
#include <optional>

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

    QVarLengthArray<std::optional<QColor>, 3> getColors();

private:
    QFile m_file;
};

#endif // LEVELLOADER_H
