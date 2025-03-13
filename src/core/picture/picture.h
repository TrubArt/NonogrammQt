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
	Picture(size_t rowCount, size_t colCount);
	Picture(const Picture&);
	~Picture();
	Picture& operator=(const Picture&);
	bool operator==(const Picture&) const;
	bool operator!=(const Picture&) const;

	// getters & setters

	const Line* getPtr(const std::pair<size_t, size_t>&) const;

	// true, если произошла закраска, иначе false
	bool setColor(size_t rowNumber, size_t index, CellType cType);

	// functions

	// выводит в консоль this, подсвечивая color различия между this и pict
	void printToConsoleDifferences(const Picture& pict, Color color) const;

	// выводит в консоль Picture, где CellType::white подсвечены цветом whiteColor, а CellType::black подсвечены цветом blackColor
	void printToConsoleColor(Color whiteColor, Color blackColor) const;
	std::string toString() const;
	friend std::ostream& operator<<(std::ostream& out, const Picture& pict); // печать изображения

private:
	// определяет необходимо ли вносить измененияв изображение или нет
	bool needChanges(size_t rowNumber, size_t index, CellType cType) const;
	void paint(size_t rowNumber, size_t index, CellType cType);
};
#endif // !PICTURE_NONOGRAM
