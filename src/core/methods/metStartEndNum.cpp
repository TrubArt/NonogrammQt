#include "metStartEndNum.h"

void StartEndNum::realization(const Condition& cond, Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex) const
{
	const Line* analyzedLine = cond.getLinePtr();
	size_t start = cond.getStart();
	size_t end = cond.getEnd();

	auto startIter = cond.getNumInfo().cbegin();
	while (analyzedLine->getCellType(start) != CellType::undefined)
	{
		if (analyzedLine->getCellType(start) == CellType::white) 
		{
			++start;
		}
		else
		{
			++start;		// тк первая клетка числа уже закрашена
			for (size_t count = 0; count <= startIter->getNum() - 1; ++count)		// закрашиваем количество клеток, равное числу
			{
				if (count < startIter->getNum() - 1)
				{
					setColorAndAddInQueue(pict, queue, isColumn, rowOrColIndex, start++, CellType::black);	// закрашиваем Number-1 клетку
				}
				else		// если count == startIter->getNum() - 1
				{
					if (start >= end)	// условие эквивалентное тому, что строка полностью закрашена
					{
						return;
					}

					setColorAndAddInQueue(pict, queue, isColumn, rowOrColIndex, start++, CellType::white);	// и добавляем в конце 0
				}
			}
			++startIter;	// переходим к следующему числу
		}

		if (start >= end)	// условие эквивалентное тому, что строка полностью закрашена
		{
			return;
		}
	}

	auto endIter = cond.getNumInfo().crbegin();
	while (analyzedLine->getCellType(end - 1) != CellType::undefined)
	{
		if (analyzedLine->getCellType(end - 1) == CellType::white) 
		{
			--end;
		}
		else
		{
			--end;		// тк первая клетка числа уже закрашена
			for (size_t count = 0; count <= endIter->getNum() - 1; ++count)
			{
				if (count < endIter->getNum() - 1)
				{
					setColorAndAddInQueue(pict, queue, isColumn, rowOrColIndex, --end, CellType::black);	// закрашиваем Number - 1 клетку
				}
				else		// если count == startIter->getNum() - 1
				{
					if (start >= end)	// условие эквивалентное тому, что строка полностью закрашена
					{
						return;
					}

					setColorAndAddInQueue(pict, queue, isColumn, rowOrColIndex, --end, CellType::white);	// и добавляем в конце 0
				}
			}
			++endIter;	// переходим к следующему числу
		}

		if (start >= end)	// условие эквивалентное тому, что строка полностью закрашена
		{
			return;
		}
	}
}

std::string StartEndNum::methodName() const
{
	return "StartEndNum";
}

std::string StartEndNum::principleOfMethodWork() const
{
	std::string answ;
	answ.append("Если в линии на позиции start или end находится CellType::black, то\n");
	answ.append("можно закрасить клетки однозначно принадлежащие первому или последнему числу.\n");
	answ.append("Метод повторяется в цикле до тех пор, пока не встретится CellType::undefined\n");
	return answ;
}
