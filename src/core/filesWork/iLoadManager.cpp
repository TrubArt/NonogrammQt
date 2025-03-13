#include "iLoadManager.h"

ILoadManager::ILoadManager(const std::string& directory, const std::vector<std::string>& files)
	: directory(directory)
	, files(files)
{}
