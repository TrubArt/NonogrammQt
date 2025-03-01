#ifndef PAINTCELLINFO_NONOGRAM
#define PAINTCELLINFO_NONOGRAM

#include <cstddef>

enum class CellType;

struct PaintCellInfo
{
	size_t rowNumber;
	size_t indexInRow;
	CellType color;

	PaintCellInfo(size_t rowNumber, size_t index, CellType color);
};

#endif // !PAINTCELLINFO_NONOGRAM
