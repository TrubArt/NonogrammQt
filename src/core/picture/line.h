#ifndef LINE_NONOGRAM
#define LINE_NONOGRAM

#include "cell.h"
#include "colorEnum.h"

#include <iostream>
#include <string>
#include <vector>

// класс линии, содержащей вектор клеток
class Line
{
	std::vector<Cell*> data;	// вектор клеток
	// REWORK переход на умные указатели

public:
	// ctors, dtor, operators

	Line() = default;
	Line(const Line&);
    Line(Line&&);
	~Line();
	Line& operator=(const Line&);
    Line& operator=(Line&&);

    Line(size_t);
	bool operator==(const Line&) const;
	bool operator!=(const Line&) const;

	// getters & setters

	void setCellType(size_t index, CellType cType);
	CellType getCellType(size_t index) const;
	size_t getSize() const;

	// functions

	// возвращает количество клеток типа cType в Line
	size_t getCountTypeCell(CellType cType) const;

	// возвращает количество клеток типа cType в диапазоне[startIndex, endIndex) в Line
	size_t getCountTypeCell(size_t startIndex, size_t endIndex, CellType cType) const;

	// возвращает первый индекс слева типа cType в диапазоне[startIndex, endIndex) в Line
	int getLeftIndexTypeCell(size_t startIndex, size_t endIndex, CellType cType) const;

	// возвращает первый индекс справа типа cType в диапазоне[startIndex, endIndex) в Line
	int getRightIndexTypeCell(size_t startIndex, size_t endIndex, CellType cType) const;

	// выводит в консоль this, подсвечивая цветом color различия между this и line
	void printToConsoleDifferences(const Line& line, Color color) const;

	// выводит в консоль Line, где CellType::white подсвечены цветом whiteColor, а CellType::black подсвечены цветом blackColor
	void printToConsoleColor(Color whiteColor, Color blackColor) const;
	std::string toString() const;
	friend std::ostream& operator<<(std::ostream& out, const Line& line);

private:
    void destruct();
};
#endif // !LINE_NONOGRAM
