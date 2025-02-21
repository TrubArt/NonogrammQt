#include "metUnambiguousWhite.h"

void UnambiguousWhite::realization(const Condition& cond, Picture* pict, const std::pair<int, int>& posit) const
{
	auto list = cond.getNumInfo();
	int leftBorder = cond.getStart();

	for (const auto& element : list)
	{
		for (int index = leftBorder; index < element.getD().first; ++index)
		{
			this->setColorWithInformation(pict, posit, index, CellType::white);
		}

		leftBorder = element.getD().second;
	}

	// анализ элементов между LastElement.getD().second и cond->getEnd()
	for (int index = leftBorder; index < cond.getEnd(); ++index)
	{
		this->setColorWithInformation(pict, posit, index, CellType::white);
	}
}

std::string UnambiguousWhite::methodName() const
{
	return "UnambiguousWhite";
}

std::string UnambiguousWhite::principleOfMethodWork() const
{
	std::string answ;
	answ.append("Проходится по всем незаконченным числам в линии. Работает с диапазоном(D).\n");
	answ.append("Находит клетки, не принадлежащие ни одному диапазону и определяет их как белые.\n");
	return answ;
}
