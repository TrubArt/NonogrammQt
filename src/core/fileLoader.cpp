#include "fileLoader.h"

#include <iostream>

FileLoader::FileLoader(const std::string& _fileName)
	: fileName(_fileName + ".txt")
	, file(fileName)
{
	if (!file.is_open())
	{
		std::cerr << "File " << fileName << " not open!\n";
		std::exit(1);
	}
}

FileLoader::~FileLoader()
{
	file.close();
}

bool FileLoader::isEmpty() const
{
	return file.eof();
}

size_t FileLoader::getNumber(const std::string& str, size_t& index) const
{
	std::string tmp;
	while (str[index] != ' ' && index < str.length())
	{
		tmp.push_back(str[index++]);
	}
	int number = std::stoi(tmp);

	if (number <= 0)
	{
		std::cerr << "Uncorrect input data.\n";
		std::cerr << "File: " << fileName << "\n";
		std::cerr << "Data: " << str << "\n";
	}

	return number;
}

std::vector<size_t> FileLoader::getNumbersSequence()
{
	std::string str;
	do								// пропуск пустых строчек
	{
		std::getline(file, str);
	} while (str.empty() && !isEmpty());

	std::vector<size_t> tmpvec;		// вектор с ответом

	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] != ' ')
		{
			tmpvec.push_back(getNumber(str, i));
		}
	}

	return tmpvec;
}
