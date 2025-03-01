#include "metUnambiguousWhite.h"

void UnambiguousWhite::realization(const Condition& cond, Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex) const
{
	auto list = cond.getNumInfo();
	size_t leftBorder = cond.getStart();

	for (const auto& element : list)
	{
		for (size_t index = leftBorder; index < element.getD().first; ++index)
		{
			setColorAndAddInQueue(pict, queue, isColumn, rowOrColIndex, index, CellType::white);
		}

		leftBorder = element.getD().second;
	}

	// анализ элементов между LastElement.getD().second и cond->getEnd()
	for (size_t index = leftBorder; index < cond.getEnd(); ++index)
	{
		setColorAndAddInQueue(pict, queue, isColumn, rowOrColIndex, index, CellType::white);
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
