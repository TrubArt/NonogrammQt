#ifndef IMETHOD_NONOGRAM
#define IMETHOD_NONOGRAM

#include "picture/picture.h"
#include "condition/condition.h"
#include "queueCells/cellQueue.h"

#include <string>

// интерфес для методов
class IMethod
{
public:
	// метод, изменяющий изображение. Входные параметры:
	// cond - условие конкретной строки/столбца
	// pict - изображение, в которое будут вноситься изменения
	// posit.first - определяет строка или столбец
	// posit.second - номер строки/столбца
	// queue - вектор с информацией о закрашенных клетках
	virtual void realization(const Condition& cond, Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex) const = 0;

	// возвращает название метода
	virtual std::string methodName() const = 0;

	// возвращает описание принципа работы метода
	virtual std::string principleOfMethodWork() const = 0;

protected:
	// совмещает в себе работу setColorWithInformation и addInfoInQueue
	void setColorAndAddInQueue(Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex, size_t lineIndex, CellType cType) const;

private:
	// закрашивает в Pict posit.first под номером posit.second позицию index цветом cType
	bool setColorWithInformation(Picture& pict, size_t rowIndex, size_t lineIndex, CellType cType) const;

	// вносит изменения в queue
	void addInfoInQueue(CellQueue& queue, size_t rowIndex, size_t lineIndex, CellType cType) const;
};

#endif // !IMETHOD_NONOGRAM
