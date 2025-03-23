#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "filesWork/iLoadManager.h"

class LevelManager : public ILoadManager
{
public:
    LevelManager();

    std::pair<size_t, size_t> getNonogramSize() override;
    std::vector<std::array<size_t, 3>> getAdditionalCondition() override;
    std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) override;

private:

};

#endif // LEVELMANAGER_H
