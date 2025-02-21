#ifndef PICTURE_NONOGRAM
#define PICTURE_NONOGRAM

#include "line.h"

#include <iostream>
#include <vector>
#include <string>

// класс, хранящий изображение
class Picture
{
	std::vector<Line*> rows;	// вектор строк
	std::vector<Line*> columns;	// вектор столбцов

public:
	// constructors, destructor, operators

	Picture() = default;
	Picture(size_t N, size_t M);
	Picture(const Picture&);
	~Picture();
	Picture& operator=(const Picture&);
	bool operator==(const Picture&) const;
	bool operator!=(const Picture&) const;

	// getters & setters

    const Line* getPtr(const std::pair<int, int>&) const;
	void setColor(int rowNumber, size_t index, CellType cType);

	// functions

	// выводит в консоль this, подсвечивая color различия между this и pict
	void printToConsoleDifferences(const Picture& pict, int color) const;

	// выводит в консоль Picture, где CellType::white подсвечены цветом whiteColor, а CellType::black подсвечены цветом blackColor
	void printToConsoleColor(int whiteColor, int blackColor) const;
	std::string toString() const;
	friend std::ostream& operator<<(std::ostream& out, const Picture& pict); // печать изображения
};
#endif // !PICTURE_NONOGRAM
