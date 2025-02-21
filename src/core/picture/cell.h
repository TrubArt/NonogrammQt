#ifndef CELL_NONOGRAM
#define CELL_NONOGRAM

#include <iostream>
#include <string>

// перечислитель для вида клетки поля
enum class CellType
{
	undefined = -1,
	white,
	black
};

// класс клетки поля
class Cell
{
	CellType cellType; //тип клетки

public:
	// ctors, dctor, operators

	Cell();
	Cell(CellType cType);

	// getters & setters

	void set(CellType cType);
	CellType get() const;

	// functions

	std::string toString() const;
	friend std::ostream& operator<<(std::ostream& out, const Cell& cell);
};
#endif // !CELL_NONOGRAM
