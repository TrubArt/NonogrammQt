#ifndef CONDITION_NONOGRAM
#define CONDITION_NONOGRAM

#include "picture/line.h"
#include "numberAndBorder.h" 

#include <string>
#include <list>

// enum для типа возращаемого значения функции updateCondition()
enum class UpdCondReturnParam
{
	lineNotCompleted = -1,
	setWhite,
	setBlack
};

// все данные о строке изменяются только в этом классе и классе NumberAndBorders
// извне данные поменять невозможно(инкапсуляция)

// класс, хранящий в себе указатель на строку и содержащий характеристики этой строки
class Condition
{
	// неизменяемые в процессе решения величины

	int allCountWhiteCell;					// общее количество белых клеток - CellType::white ('0')
	int allCountBlackCell;					// общее количество чёрных клеток - CellType::black ('1')
	const Line* data;						// константный указатель на соответствующий Line

	// изменяемые в процессе решения величины

	bool isFull;							// индикатор того заполнена ли строка полностью
	int start;								// индекс первой CellType::undefined ('*')
	int end;								// индекс после последней CellType::undefined ('*')
	Line statLine;							// запоминает состояние строки для сравнения с data
	std::list<NumberAndBorders> numInfo;	// список, хранящий все числа из data

public:
	// ctors, dtor, operators

	Condition();
	Condition(size_t lineSize, const Line* ptr, const std::vector<int>& info);

	// getters & setters

	bool getIsFullFlag() const;
	const Line* getLinePtr() const;
	int getStart() const;
	int getEnd() const;
	const std::list<NumberAndBorders>& getNumInfo() const;

	// functions

	UpdCondReturnParam updateCondition();

	// выводит в консоль this, подсвечивая color различия между this и cond
	void printToConsoleDifferences(const Condition& cond, int color) const;
	std::string toString() const;

private:
	void updateStart();
	void updateEnd();
	void updateBorders();

	// обновляет Dia(если новые границы лучше старых), проверяя для каждого числа границы его существования
	// при максимально плотной расстановке всех чисел кроме данного
	void updateDia();

	// обновляет realDia(если новые границы лучше старых), проверяя 
	// существует ли диапазон между реальными границами соседних чисел
	void updateRealDia();
};
#endif // !CONDITION_NONOGRAM
