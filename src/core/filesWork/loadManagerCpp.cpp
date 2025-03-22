#include "loadManagerCpp.h"
#include "fileLoaderCpp.h"

#include <iostream>

LoadManagerCpp::LoadManagerCpp(const std::string& directory, const std::vector<std::string>& files)
	: ILoadManager(directory, files)
	, fileLoader(std::make_unique<FileLoaderCpp>())
{
	if (files.size() != 3)
	{
		std::cerr << "Class FileLoaderCpp must have only 3 files:\n"
			<< "additional color condition.txt\n"
			<< "condition.txt\n"
			<< "size.txt\n";
		std::exit(1);
	}
}

std::pair<size_t, size_t> LoadManagerCpp::getNonogramSize()
{
	std::string conditionFile = directory + directoryDelimeter + files[2];
	if (fileLoader->getFileName() != conditionFile)
	{
		fileLoader->setFile(conditionFile);
	}

	return fileLoader->getNonogramSize();
}

std::vector<std::array<size_t, 3>> LoadManagerCpp::getAdditionalCondition()
{
	std::string conditionFile = directory + directoryDelimeter + files[0];
	if (fileLoader->getFileName() != conditionFile)
	{
		fileLoader->setFile(conditionFile);
	}
	
	return fileLoader->getAdditionalCondition();
}

std::vector<size_t> LoadManagerCpp::getLineSequence(bool isColumn, size_t lineIndex)
{
	std::string conditionFile = directory + directoryDelimeter + files[1];
	if (fileLoader->getFileName() != conditionFile)
	{
		fileLoader->setFile(conditionFile);
	}

	return fileLoader->getLineSequence(isColumn, lineIndex);
}