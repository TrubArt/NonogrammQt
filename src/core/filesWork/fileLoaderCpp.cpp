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

std::vector<std::array<size_t, 3>> FileLoaderCpp::getAdditionalCondition()
{
	std::vector<std::array<size_t, 3>> allConditions;

	constexpr int mustCountNumberInRow = 3;
	size_t strNumber = 1;

	while (!isEndOfFile())
	{
		std::vector<size_t> oneConditionVector = getLineSequence(false, 0);
		if (!oneConditionVector.empty())
		{
			if (oneConditionVector.size() != mustCountNumberInRow)
			{
				std::cerr	<< "Error in read " << fileName << "\n"
							<< "Count number in Line = " << oneConditionVector.size() << ". Must be " << mustCountNumberInRow << ".\n"
							<< "Line : " << strNumber << "!\n";
				std::exit(1);
			}

			std::array<size_t, 3> oneCondition = { oneConditionVector[0], oneConditionVector[1], oneConditionVector[2] };
			allConditions.push_back(oneCondition);
		}
		++strNumber;
	}

	return allConditions;
}

std::pair<size_t, size_t> FileLoaderCpp::getNonogramSize()
{
	std::vector<size_t> line = getLineSequence(false, 0);
	if (line.size() < 2)
	{
		std::cerr << "Incorrect data in" << fileName;
		return std::make_pair(0, 0);
	}
	return std::make_pair(line[0], line[1]);
}

bool FileLoaderCpp::isEndOfFile() const
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
		std::cerr	<< "Uncorrect input data.\n"
					<< "File: " << fileName << "\n"
					<< "Data: " << str << "\n";
	}

	return numberToInt;
}

std::string FileLoaderCpp::skipEmptyFileLine()
{
	std::string str;
	do
	{
		std::getline(file, str);
	} while (str.empty() && !isEndOfFile());

	return str;
}
