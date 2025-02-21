#include "cell.h"

Cell::Cell() : cellType(CellType::undefined)
{}

Cell::Cell(CellType cType) : cellType(cType)
{}

void Cell::set(CellType cType)
{
	cellType = cType;
}

CellType Cell::get() const
{
	return cellType;
}

std::string Cell::toString() const
{
	return cellType == CellType::undefined ? "*" : std::to_string(static_cast<int>(cellType));
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	out << cell.toString();
	return out;
}
