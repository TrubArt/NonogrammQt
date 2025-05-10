#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QDir>

#include "filesWork/iLoadManager.h"
#include "levelData.h"

class LevelManager : public ILoadManager
{
public:
    LevelManager();

    void setDirectoryAndData(const QDir& dir, std::shared_ptr<LevelData> loadedData);
    void returnToDefault();

    std::pair<size_t, size_t> getNonogramSize() override;
    std::vector<std::array<size_t, 3>> getAdditionalCondition() override;
    std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) override;
    ColorStore getNonogramColors();

    void saveAll();

private:
    void saveProperties();
    void saveData();

    QDir m_levelDir;
    std::shared_ptr<LevelData> m_loadedData;

    const QString additionDataFile =  "Additional color condition.txt";
    const QString conditionDataFile = "Condition.txt";
    const QString infoDataFile = "Info.txt";
};

#endif // LEVELMANAGER_H
