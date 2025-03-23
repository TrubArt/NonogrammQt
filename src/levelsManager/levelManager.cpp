#include "levelManager.h"
#include "levelLoader.h"

LevelManager::LevelManager()
    : ILoadManager(new LevelLoader())
{

}

std::pair<size_t, size_t> LevelManager::getNonogramSize() { return {}; }
std::vector<std::array<size_t, 3>> LevelManager::getAdditionalCondition() { return {}; }
std::vector<size_t> LevelManager::getLineSequence(bool isColumn, size_t lineIndex) { return {}; }
