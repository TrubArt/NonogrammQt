#include "PaintCellInfo.h"

PaintCellInfo::PaintCellInfo(size_t rowNumber, size_t index, CellType color)
	: rowNumber(rowNumber)
	, indexInRow(index)
	, color(color)
{}