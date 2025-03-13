#include "fileLoaderCpp.h"

#include <iostream>

FileLoaderCpp::FileLoaderCpp(const std::string& _fileName)
	: fileName(_fileName + suf)
	, file(fileName)
{
	if (!file.is_open())
	{
		std::cerr << "File " << fileName << " not open!\n";
		std::exit(1);
	}
}

FileLoaderCpp::~FileLoaderCpp()
{
	file.close();
}

void FileLoaderCpp::setFile(const std::string& _fileName)
{
	file.close();
	fileName = _fileName + suf;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "File " << fileName << " not open!\n";
		std::exit(1);
	}
}

std::string FileLoaderCpp::getFileName() const
{
	std::string oldFileName = fileName;
	if (!fileName.empty())
	{
		oldFileName.erase(fileName.size() - suf.size());
	}
	return oldFileName;
}

std::vector<std::vector<size_t>> FileLoaderCpp::getAdditionalCondition()
{
	std::vector<std::vector<size_t>> allConditions;

	while (!isEmpty())
	{
		std::vector<size_t> oneCondition = getLineSequence(false, 0);
		if (!oneCondition.empty())
		{
			allConditions.push_back(oneCondition);
		}
	}

	return allConditions;
}

std::pair<size_t, size_t> FileLoaderCpp::getNonogramSize()
{
	std::vector<size_t> line = getLineSequence(false, 0);
	if (line.empty())
	{
		std::cerr << "Dont find any numbers in " << fileName;
		return std::make_pair(0, 0);
	}
	return std::make_pair(line[0], line[1]);
}

bool FileLoaderCpp::isEmpty() const
{
	return file.eof();
}

std::vector<size_t> FileLoaderCpp::getLineSequence(bool, size_t)
{
	std::string strFromFile = skipEmptyFileLine();

	std::vector<size_t> sequence;
	for (size_t i = 0; i < strFromFile.length(); ++i)
	{
		if (strFromFile[i] != ' ')
		{
			sequence.push_back(getNumber(strFromFile, i));
		}
	}

	return sequence;
}

size_t FileLoaderCpp::getNumber(const std::string& str, size_t& index) const
{
	std::string number;
	while (str[index] != ' ' && index < str.length())
	{
		number.push_back(str[index++]);
	}
	int numberToInt = std::stoi(number);

	if (numberToInt < 0)
	{
		std::cerr << "Uncorrect input data.\n";
		std::cerr << "File: " << fileName << "\n";
		std::cerr << "Data: " << str << "\n";
	}

	return numberToInt;
}

std::string FileLoaderCpp::skipEmptyFileLine()
{
	std::string str;
	do
	{
		std::getline(file, str);
	} while (str.empty() && !isEmpty());

	return str;
}
