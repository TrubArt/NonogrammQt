#ifndef NUMBER_NONOGRAM
#define NUMBER_NONOGRAM

#include "picture/line.h"

#include <string>

// класс, хранящий число и его характеристики
class NumberAndBorders
{
	using myP = std::pair<size_t, size_t>;

	size_t number;	// число
	myP dia;		// (D) диапазон, в котором может теоретически находиться число
	bool isExistRD;	// флаг, показывающий, существует ли реальный диапазон
	myP realDia;	// (RD) диапазон, в котором находится только это число

public:
	// ctors, dtor, operators

	NumberAndBorders(size_t number, const myP& dia, const myP& realdia);

	// getters & setters

	size_t getNum() const;
    const myP& getD() const;
    const myP& getRD() const;
	bool getFlagExistRd() const;
	void setD(const myP& x);
	void setFlagExistRd(bool flag);
	void setRD(const myP& x);

	// functions

	void updateNumberAndBorders(const Line* data);

	// выводит в консоль this, подсвечивая color различия между this и data
	void printToConsoleDifferences(const NumberAndBorders& data, Color color) const;
	std::string toString() const;

private:
	// приближает RD до границ D, тк RD не может выходить за пределы D
	void updateRDviaD();

	// уменьшает D, если на краях число не помещается из-за расположения 0
	void updateDIfWhiteInEdges(const Line* data);

	// улучшает D, если в RD есть хоть одна black клетка
	// недосягаемость https://www.nonograms.ru/methods
	void updateDviaRD(const Line* data);
};
#endif // !NUMBER_NONOGRAM
