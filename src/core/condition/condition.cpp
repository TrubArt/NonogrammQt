#include "condition.h"

Condition::Condition()
	: allCountWhiteCell(0)
	, allCountBlackCell(0)
	, data(nullptr)
	, isFull(false)
	, start(0)
	, end(0)
{}

Condition::Condition(size_t lineSize, const Line* ptr, const std::vector<size_t>& info)
	: allCountBlackCell(0)
	, data(ptr)
	, isFull(false)
	, start(0)
	, end(lineSize)
	, statLine(lineSize + 1) // делаем *data != statLine
{
	for (size_t i = 0; i < info.size(); ++i)
	{
		// данные для диапазонов передаются именно в таком формате, поскольку D - должен только сужаться, а RD - расширяться
		numInfo.push_back(NumberAndBorders(info[i], std::make_pair(start, end), std::make_pair(end, start)));
	}

	for (const auto& i : numInfo)
	{
		allCountBlackCell += i.getNum();
	}
	allCountWhiteCell = lineSize - allCountBlackCell;

	updateBorders();
}

size_t Condition::getAllCountWhiteCell() const
{
	return allCountWhiteCell;
}

size_t Condition::getAllCountBlackCell() const
{
	return allCountBlackCell;
}

bool Condition::getIsFullFlag() const
{
	return isFull;
}

const Line* Condition::getLinePtr() const
{
	return data;
}

size_t Condition::getStart() const
{
	return start;
}

size_t Condition::getEnd() const
{
	return end;
}

const std::list<NumberAndBorders>& Condition::getNumInfo() const
{
	return numInfo;
}

void Condition::updateCondition()
{
	if (*data == statLine)
	{
		return;
	}

	// проверка на то, что строку можно однозначно определить
	if (data->getCountTypeCell(CellType::white) == allCountWhiteCell
		|| data->getCountTypeCell(CellType::black) == allCountBlackCell)
	{
		isFull = true;
		return;
	}

	statLine = *data; // обновляем состояние строки до актуального

	// обновление start
	updateStart();

	// обновление end
	updateEnd();

	// обновление диапазонов в numInfo
	updateBorders();
}

void Condition::printToConsoleDifferences(const Condition& cond, Color color) const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD lightDifferens = static_cast<WORD>(color);
	WORD undefinedColor = static_cast<WORD>(Color::white);

	if (isFull)
	{
		if (isFull != cond.isFull)
		{
			SetConsoleTextAttribute(console, lightDifferens);
		}
		std::cout << "-\n";
		SetConsoleTextAttribute(console, undefinedColor);
		return;
	}

	std::cout << "\tStart: ";

	if (start != cond.start)
	{
		SetConsoleTextAttribute(console, lightDifferens);
	}
	std::cout << start;
	SetConsoleTextAttribute(console, undefinedColor);

	std::cout << ", End: ";

	if (end != cond.end)
	{
		SetConsoleTextAttribute(console, lightDifferens);
	}
	std::cout << end;
	SetConsoleTextAttribute(console, undefinedColor);

	std::cout << "\n\tList:";

	for (auto thisIt = numInfo.cbegin(), condIt = cond.numInfo.cbegin(); thisIt != numInfo.cend(); ++thisIt, ++condIt)
	{
		std::cout << " ";
		thisIt->printToConsoleDifferences((*condIt), color);
	}

	std::cout << "\n";
}

std::string Condition::toString() const
{
	if (isFull)
	{
		return "-\n";
	}

	std::string answer;
	answer.append("\tStart: " + std::to_string(start) + ", End: " + std::to_string(end) + "\n");
	answer.append("\tList:");

	for (const auto& i : numInfo)
	{
		answer.append(" " + i.toString());
	}

	return answer.append("\n");
}

void Condition::updateStart()
{
	if (start >= end)
	{
		return;
	}

	while (data->getCellType(start) != CellType::undefined)
	{
		if (data->getCellType(start) == CellType::white)
		{
			++start;
		}
		else
		{
			// данный случай обрабатывается методом StartEndNum. Он закрашивает необходимые клетки.
			// здесь же остаётся только обновить данные о начале
			size_t number = numInfo.front().getNum();
			numInfo.pop_front();
			start += number + 1;
		}

		if (start >= end)
		{
			return;
		}
	}
}

void Condition::updateEnd()
{
	if (start >= end)
	{
		return;
	}

	while (data->getCellType(end - 1) != CellType::undefined)
	{
		if (data->getCellType(end - 1) == CellType::white)
		{
			--end;
		}
		else
		{
			// данный случай обрабатывается методом StartEndNum. Он закрашивает необходимые клетки.
			// здесь же остаётся только обновить данные о конце
			size_t number = numInfo.back().getNum();
			numInfo.pop_back();
			end -= number + 1;
		}

		if (start >= end)
		{
			return;
		}
	}
}

void Condition::updateBorders()
{
	updateDia();
	updateRealDia();
	for (auto& i : numInfo)
	{
		i.updateNumberAndBorders(data);
	}
}

void Condition::updateDia()
{
	enum HelpEnum {space = 1};	// enum обозначающий пробел(одна CellType::whiteCell)

	size_t rightNums = end;		// количество занятых клеток справа от текущего числа

	// подсчёт оптимальной правой границы для первого числа
	for (auto it = numInfo.cbegin(); it != numInfo.cend(); ++it)
	{
		rightNums -= it->getNum() + space;
	}

	size_t leftNums = start;		// количество занятых клеток слева от текущего числа

	// подсчёт для каждого числа нового диапазона
	for (auto it = numInfo.begin(); it != numInfo.end(); ++it)
	{
		rightNums += it->getNum() + space;	// добавление текущего числа для анализа и пересмотр его правой границы

		if (leftNums > it->getD().first)	// улучшениe startDia
		{
			it->setD(std::make_pair(leftNums, it->getD().second));
		}
		if (rightNums < it->getD().second)	// улучшениe endDia
		{
			it->setD(std::make_pair(it->getD().first, rightNums));
		}

		leftNums += it->getNum() + space;	// удаление текущего числа из анализа, изменение левой границы для следующего числа
	}
}

void Condition::updateRealDia()
{
	size_t leftBorder = start;
	size_t rightBorder = 0;

	for (auto it = numInfo.begin(); it != numInfo.end(); ++it)
	{
		auto ittmp = it;
		// определение rightBorder
		if (it == --numInfo.end())
		{
			rightBorder = end;
		}
		else
		{
			rightBorder = (++ittmp)->getD().first;
		}

		if (leftBorder < rightBorder)	// проверка что в таком диапазоне есть хотя бы 1 клетка
		{
			it->setFlagExistRd(true);	// найден реальный диапазон

			if (leftBorder < it->getRD().first)		// улучшениe startRDia
			{
				it->setRD(std::make_pair(leftBorder, it->getRD().second));
			}
			if (rightBorder > it->getRD().second)	// улучшениe endRDia
			{
				it->setRD(std::make_pair(it->getRD().first, rightBorder));
			}
		}

		// определение next leftBorder
		leftBorder = it->getD().second;
	}
}
