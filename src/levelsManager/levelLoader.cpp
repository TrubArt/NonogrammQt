#include "levelLoader.h"

LevelLoader::LevelLoader()
{

}

void LevelLoader::setFile(const std::string& fileName) {}
std::string LevelLoader::getFileName() const { return {}; }

std::pair<size_t, size_t> LevelLoader::getNonogramSize() { return {}; }
std::vector<std::array<size_t, 3>> LevelLoader::getAdditionalCondition() { return {}; }
std::vector<size_t> LevelLoader::getLineSequence(bool isColumn, size_t lineIndex) { return {}; }
