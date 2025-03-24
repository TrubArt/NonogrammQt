#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QDir>
#include <optional>

#include "filesWork/iLoadManager.h"
#include "levelData.h"

class LevelManager : public ILoadManager
{
public:
    LevelManager();

    void setDirectoryAndData(const QDir& dir, const std::optional<LevelData>& loadedData);

    std::pair<size_t, size_t> getNonogramSize() override;
    std::vector<std::array<size_t, 3>> getAdditionalCondition() override;
    std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) override;

private:
    QDir m_levelDir;
    std::optional<LevelData> m_loadedData;

    const std::string additionDataFile =  "additional color condition.txt";
    const std::string conditionDataFile = "condition.txt";
    const std::string infoDataFile = "info.txt";
};

#endif // LEVELMANAGER_H
