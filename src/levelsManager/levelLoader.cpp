#include "levelLoader.h"

LevelLoader::LevelLoader(QDir levelDirectory)
{}

std::pair<size_t, size_t> LevelLoader::getNonogramSize() { return {}; }
std::vector<std::array<size_t, 3>> LevelLoader::getAdditionalCondition() { return {}; }
std::vector<size_t> LevelLoader::getLineSequence(bool isColumn, size_t lineIndex) { return {}; }

const LevelData& LevelLoader::getData() const
{
    return m_levelData;
}

LevelData& LevelLoader::getData()
{
    return m_levelData;
}
