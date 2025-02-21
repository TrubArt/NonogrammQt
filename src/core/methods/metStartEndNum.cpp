#include "metStartEndNum.h"

void StartEndNum::realization(const Condition& cond, Picture* pict, const std::pair<int, int>& posit) const
{
	const Line* analyzedLine = cond.getLinePtr();
	int start = cond.getStart();
	int end = cond.getEnd();

	std::list<NumberAndBorders>::const_iterator startIter = cond.getNumInfo().cbegin();
	while (analyzedLine->getCellType(start) != CellType::undefined)
	{
		if (analyzedLine->getCellType(start) == CellType::white) 
		{
			++start;
		}
		else
		{
			++start;		// тк первая клетка числа уже закрашена
			for (int count = 0; count <= (*startIter).getNum() - 1; ++count)		// закрашиваем количество клеток, равное числу
			{
				if (count < (*startIter).getNum() - 1)
				{
					this->setColorWithInformation(pict, posit, start++, CellType::black);	// закрашиваем Number-1 клетку
				}
				else		// если count == (*startIter).getNum() - 1
				{
					if (start >= end)	// условие эквивалентное тому, что строка полностью закрашена
					{
						return;
					}
					this->setColorWithInformation(pict, posit, start++, CellType::white);	// и добавляем в конце 0
				}
			}
			++startIter;	// переходим к следующему числу
		}
		if (start >= end)	// условие эквивалентное тому, что строка полностью закрашена
		{
			return;
		}
	}

	std::list<NumberAndBorders>::const_reverse_iterator endIter = cond.getNumInfo().crbegin();
	while (analyzedLine->getCellType(end - 1) != CellType::undefined)
	{
		if (analyzedLine->getCellType(end - 1) == CellType::white) 
		{
			--end;
		}
		else
		{
			--end;		// тк первая клетка числа уже закрашена
			for (int count = 0; count <= (*endIter).getNum() - 1; ++count)
			{
				if (count < (*endIter).getNum() - 1)
				{
					this->setColorWithInformation(pict, posit, --end, CellType::black);	// закрашиваем Number-1 клетку
				}
				else		// если count == (*startIter).getNum() - 1
				{
					if (start >= end)	// условие эквивалентное тому, что строка полностью закрашена
					{
						return;
					}
					this->setColorWithInformation(pict, posit, --end, CellType::white);	// и добавляем в конце 0
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
