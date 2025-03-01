#include "metLastColorSet.h"

void LastColorSet::realization(const Condition& cond, Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex) const
{
	const Line* analyzedLine = cond.getLinePtr();

	CellType remainedColorCells = CellType::undefined;
	if (analyzedLine->getCountTypeCell(CellType::white) == cond.getAllCountWhiteCell())
	{
		remainedColorCells = CellType::black;
	}
	if (analyzedLine->getCountTypeCell(CellType::black) == cond.getAllCountBlackCell())
	{
		remainedColorCells = CellType::white;
	}

	if (remainedColorCells == CellType::undefined)
	{
		return;
	}

	for (size_t index = cond.getStart(); index < cond.getEnd(); ++index)
	{
		if (analyzedLine->getCellType(index) != CellType::undefined)
		{
			continue;
		}

		setColorAndAddInQueue(pict, queue, isColumn, rowOrColIndex, index, remainedColorCells);
	}
}

std::string LastColorSet::methodName() const
{
	return "LastColorSet";
}

std::string LastColorSet::principleOfMethodWork() const
{
	std::string answ;
	answ.append("Если количество закрашенных белых(чёрных) клеток совпадает с общим количеством белых(чёрных) клеток, то\n");
	answ.append("необходимо все оставшиеся клетки CellType::undefined закрасить в чёрный(белый) цвет");
	return answ;
}
