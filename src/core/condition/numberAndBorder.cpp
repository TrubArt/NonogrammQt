#include "numberAndBorder.h"

NumberAndBorders::NumberAndBorders(size_t number, const myP& dia, const myP& realdia) 
	: dia(dia), realDia(realdia), number(number), isExistRD(false) 
{}

size_t NumberAndBorders::getNum() const
{
	return number;
}

const NumberAndBorders::myP& NumberAndBorders::getD() const
{
	return dia;
}

const NumberAndBorders::myP& NumberAndBorders::getRD() const
{
	return realDia;
}

bool NumberAndBorders::getFlagExistRd() const
{
	return isExistRD;
}

void NumberAndBorders::setD(const myP& x)
{
	dia = x;
}

void NumberAndBorders::setFlagExistRd(bool flag)
{
	isExistRD = flag;
}

void NumberAndBorders::setRD(const myP& x)
{
	realDia = x;
}

void NumberAndBorders::updateNumberAndBorders(const Line* data)
{
	updateDIfWhiteInEdges(data);
	updateRDviaD();
	updateDviaRD(data);
}

void NumberAndBorders::printToConsoleDifferences(const NumberAndBorders& data, Color color) const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD lightDifferens = static_cast<WORD>(color);
	WORD undefinedColor = static_cast<WORD>(Color::white);
	SetConsoleTextAttribute(console, undefinedColor);

	std::cout << number << "{D[";

	if (dia.first != data.dia.first)
	{
		SetConsoleTextAttribute(console, lightDifferens);
	}
	std::cout << dia.first;
	SetConsoleTextAttribute(console, undefinedColor);

	std::cout << ",";

	if (dia.second != data.dia.second)
	{
		SetConsoleTextAttribute(console, lightDifferens);
	}
	std::cout << dia.second;
	SetConsoleTextAttribute(console, undefinedColor);

	std::cout << "), RD[";

	if (isExistRD)
	{
		if (realDia.first != data.realDia.first)
		{
			SetConsoleTextAttribute(console, lightDifferens);
		}
		std::cout << realDia.first;
		SetConsoleTextAttribute(console, undefinedColor);

		std::cout << ",";

		if (realDia.second != data.realDia.second)
		{
			SetConsoleTextAttribute(console, lightDifferens);
		}
		std::cout << realDia.second;
		SetConsoleTextAttribute(console, undefinedColor);
	}
	else
	{
		std::cout << "NaN";
	}

	std::cout << ")}";
}

std::string NumberAndBorders::toString() const
{
	std::string answer;
	answer.append(std::to_string(number) +
		"{D[" + std::to_string(dia.first) + "," + std::to_string(dia.second) + "), RD[");

	if (isExistRD)
	{
		answer.append(std::to_string(realDia.first) + "," + std::to_string(realDia.second));
	}
	else
	{
		answer.append("NaN");
	}

	answer.append(")}");
	return answer;
}

void NumberAndBorders::updateRDviaD()
{
	if (!isExistRD)
	{
		return;
	}

	if (realDia.first < dia.first)
	{
		realDia.first = dia.first;
	}

	if (realDia.second > dia.second)
	{
		realDia.second = dia.second;
	}
}

void NumberAndBorders::updateDIfWhiteInEdges(const Line* data)
{
	int leftWhite = data->getLeftIndexTypeCell(dia.first, dia.second, CellType::white);		// первый левый CellType::white в D
	while (leftWhite != -1 && leftWhite - dia.first < number)	// если leftWhite находится и расстояние от него до dia.first меньше самого number,
	{	
		dia.first = leftWhite + 1;								// то number туда не поместится, соответственно сдвигаем границу
		leftWhite = data->getLeftIndexTypeCell(dia.first, dia.second, CellType::white);
	}

	int rightWhite = data->getRightIndexTypeCell(dia.first, dia.second, CellType::white);	// первый правый CellType::white в D
	while (rightWhite != -1 && (dia.second - 1) - rightWhite < number)		// если rightWhite находится и расстояние от него до dia.second меньше самого number,
	{
		dia.second = rightWhite;											// то number туда не поместится, соответственно сдвигаем границу
		rightWhite = data->getRightIndexTypeCell(dia.first, dia.second, CellType::white);
	}
}

void NumberAndBorders::updateDviaRD(const Line* data)
{
	int leftBlack = data->getLeftIndexTypeCell(realDia.first, realDia.second, CellType::black);
	if (leftBlack == -1)
	{
		// эквивалентно тому, что чёрных клеток нет
		return;
	}

	size_t rightBlack = data->getRightIndexTypeCell(realDia.first, realDia.second, CellType::black);
	size_t countOfPossibleCells = rightBlack - leftBlack + 1;
	size_t countOfRemainingCells = number - countOfPossibleCells;

	// обязательно int, тк при вычислениях может получиться отрицательное число
	int possiblyLeftBorder = leftBlack - static_cast<int>(countOfRemainingCells);
	if (possiblyLeftBorder >= 0 && dia.first < possiblyLeftBorder)
	{
		dia.first = possiblyLeftBorder;
	}


	size_t possiblyRightBorder = rightBlack + countOfRemainingCells + 1;
	if (dia.second > possiblyRightBorder)
	{
		dia.second = possiblyRightBorder;
	}

	updateRDviaD();
}
