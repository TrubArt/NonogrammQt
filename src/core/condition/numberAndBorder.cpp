#include "numberAndBorder.h"

#define NOMINMAX
#include <Windows.h>

NumberAndBorders::NumberAndBorders(int number, const myP& dia, const myP& realdia) 
	: dia(dia), realDia(realdia), number(number), isExistRD(false) 
{}

int NumberAndBorders::getNum() const
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
	this->updateDIf0InEdges(data);
	this->updateRDviaD();
	this->updateDviaRD(data);
}

void NumberAndBorders::printToConsoleDifferences(const NumberAndBorders& data, int color) const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 15);

	std::cout << number << "{D[";

	if (dia.first != data.dia.first)
	{
		SetConsoleTextAttribute(console, 4);
	}
	std::cout << dia.first;
	SetConsoleTextAttribute(console, 15);

	std::cout << ",";

	if (dia.second != data.dia.second)
	{
		SetConsoleTextAttribute(console, 4);
	}
	std::cout << dia.second;
	SetConsoleTextAttribute(console, 15);

	std::cout << "), RD[";

	if (isExistRD)
	{
		if (realDia.first != data.realDia.first)
		{
			SetConsoleTextAttribute(console, 4);
		}
		std::cout << realDia.first;
		SetConsoleTextAttribute(console, 15);

		std::cout << ",";

		if (realDia.second != data.realDia.second)
		{
			SetConsoleTextAttribute(console, 4);
		}
		std::cout << realDia.second;
		SetConsoleTextAttribute(console, 15);
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

void NumberAndBorders::updateDIf0InEdges(const Line* data)
{
	int leftBlack = data->getLeftIndexTypeCell(dia.first, dia.second, CellType::white);		// первый левый CellType::white в D
	while (leftBlack != -1 && leftBlack - dia.first < number) {	// если leftBlack находится и расстояние от него до dia.first меньше самого number,
		dia.first = leftBlack + 1;								// то number туда не поместится, соответственно сдвигаем границу
		leftBlack = data->getLeftIndexTypeCell(dia.first, dia.second, CellType::white);
	}

	int rightBlack = data->getRightIndexTypeCell(dia.first, dia.second, CellType::white);	// первый правый CellType::white в D
	while (rightBlack != -1 && (dia.second - 1) - rightBlack < number) {	// если rightBlack находится и расстояние от него до dia.second меньше самого number,
		dia.second = rightBlack;											// то number туда не поместится, соответственно сдвигаем границу
		rightBlack = data->getRightIndexTypeCell(dia.first, dia.second, CellType::white);
	}
}

void NumberAndBorders::updateDviaRD(const Line* data)
{
	int numberOfBlack = data->getCountTypeCell(realDia.first, realDia.second, CellType::black);
	if (numberOfBlack != 0)
	{
		int leftBlack = data->getLeftIndexTypeCell(realDia.first, realDia.second, CellType::black);
		int rightBlack = data->getRightIndexTypeCell(realDia.first, realDia.second, CellType::black);

		if (dia.first < leftBlack - (number - numberOfBlack))
		{
			dia.first = leftBlack - (number - numberOfBlack);
		}
		if (dia.second > rightBlack + (number - numberOfBlack) + 1)
		{
			dia.second = rightBlack + (number - numberOfBlack) + 1;
		}

		this->updateRDviaD();
	}
}
