#ifndef SOLUTION_NONOGRAM
#define SOLUTION_NONOGRAM

#include "picture/picture.h"
#include "condition/condition.h"
#include "methods/iMethod.h"
#include "methods/methodsVectorShell.h"
#include "queueCells/cellQueue.h"

#include <array>
#include <vector>
#include <string>

// основной класс, реализующий методы по решению нонограммы
class Solution
{
	Picture pict;										// изображение в котором закрашиваются клетки
	std::array<std::vector<Condition>, 2> conditions;	// массив с условиями для строк и столбцов

	static const MethodsVectorShell methods;			// набор методов для анализа
	CellQueue queue;									// очередь в которой хранятся данные о закрашенных клетках

public:
	// ctors, dctor, operators
	
	Solution() = default;

	/// <param name="fileCondition:">файл с условиями строк</param>
	/// <param name="fileAdditCondit:">файл с доп условиями цвета</param>
	Solution(const std::string& fileCondition, const std::string& fileAdditCondit);

	// getters & setters

	Picture getPicture() const;
	bool isEndOfWork() const;
	CellQueue getQueue() const;

	// functions

	bool nonogramSolution();

	// выводит в консоль this, подсвечивая color различия между this и copy
	void printToConsoleDifferences(const Solution& copy, Color color) const;
	std::string pictToString() const;
	std::string conditionsToString() const;
private:
	// метод, представляющий из себя шаблон для прогонки каждого метода
	void callingMethods();
};
#endif // !SOLUTION_NONOGRAM
