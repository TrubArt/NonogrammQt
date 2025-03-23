#include "levelManager.h"
#include "levelLoader.h"

LevelManager::LevelManager()
    : ILoadManager(new LevelLoader())
{

}

void LevelManager::setDirectoryAndData(const QDir& dir, const std::optional<LevelData>& loadedData)
{
    m_levelDir = dir;
    m_loadedData = loadedData;
}

std::pair<size_t, size_t> LevelManager::getNonogramSize() { return {}; }
std::vector<std::array<size_t, 3>> LevelManager::getAdditionalCondition() { return {}; }
std::vector<size_t> LevelManager::getLineSequence(bool isColumn, size_t lineIndex) { return {}; }
