#include "solution.h"
#include "fileLoader.h"
#include "methods/metLastColorSet.h"
#include "methods/metStartEndNum.h"

const MethodsVectorShell Solution::methods = MethodsVectorShell();

Solution::Solution(const std::string& fileCondition, const std::string& fileAdditCondit)
{
	// enum для обращения к строкам/столбцам в conditions
	enum LineClassifier { row, col };

	FileLoader cond(fileCondition);

	std::vector<size_t> tmp;

	// получение данных о размере изображения
	tmp = cond.getNumbersSequence();
	size_t sizeN = tmp[0];
	size_t sizeM = tmp[1];

	pict = Picture(sizeN, sizeM);
	conditions[row].resize(sizeN);
	conditions[col].resize(sizeM);

	// сначала добавление изначально заданных клеток
	FileLoader f2(fileAdditCondit);

	while (!f2.isEmpty())
	{
		tmp = f2.getNumbersSequence();
		if (!tmp.empty())
		{
			PaintCellInfo cellInfo(tmp[0], tmp[1], static_cast<CellType>(tmp[2]));
			if (pict.setColor(cellInfo.rowNumber, cellInfo.indexInRow, cellInfo.color))
			{
				queue.customPush(cellInfo);
			}
		}
	}

	// потом получение данных о строках и столбцах
	for (size_t i = 0; i < sizeN; ++i)
	{
		conditions[row][i] = Condition(sizeM, pict.getPtr(std::make_pair(row, i)), cond.getNumbersSequence());
	}
	for (size_t i = 0; i < sizeM; ++i)
	{
		conditions[col][i] = Condition(sizeN, pict.getPtr(std::make_pair(col, i)), cond.getNumbersSequence());
	}
}

Picture Solution::getPicture() const
{
	return pict;
}

bool Solution::isEndOfWork() const
{
	for (size_t i = 0; i < conditions.size(); ++i)
	{
		for (size_t j = 0; j < conditions[i].size(); ++j)
		{
			if (!conditions[i][j].getIsFullFlag())
			{
				return false;
			}
		}
	}
	return true;
}

CellQueue Solution::getQueue() const
{
	return queue;
}

void Solution::callingMethods()
{
	// копия, с которой будет сравниваться *this для вывода изменений в консоль
	Solution copy = *this;

	// цикл с прогоном всех методов
	for (const auto& method : methods.get())
	{
		// двойной цикл для прохода по всем строкам/столбцам
		for (size_t rowOrCol = 0; rowOrCol < conditions.size(); ++rowOrCol)
		{
			for (size_t lineNumber = 0; lineNumber < conditions[rowOrCol].size(); ++lineNumber)
			{
				Condition& curentCond = conditions[rowOrCol][lineNumber];

				if (curentCond.getIsFullFlag())		// если строка уже завершена
				{
					continue;
				}

				// вызов определённого метода					
				method->realization(curentCond, pict, queue, rowOrCol, lineNumber);

				// метод по определению числа с края строки
				StartEndNum().realization(curentCond, pict, queue, rowOrCol, lineNumber);

				// обязательный метод перед updateCondition()
				LastColorSet().realization(curentCond, pict, queue, rowOrCol, lineNumber);

				// изменение данных о строке после цикла
				curentCond.updateCondition();
			}
		}

		// вывод в консоль изменений после работы метода

		std::cout << "\nChanges after " << method->methodName() << " method work:\n\n";
		printToConsoleDifferences(copy, Color::crimson);

		copy = *this;
	}
}

bool Solution::nonogramSolution()
{
	size_t step = 0;
	bool noChangesAfterCycle = false;

	while (!noChangesAfterCycle && !isEndOfWork())
	{
		std::cout << "--------------------step" << ++step << "--------------------\n";

		Picture pictureToCompare{ pict };

		// работа методов
		callingMethods();

		// если после работы методов нет изменений
		if (pictureToCompare == pict && !isEndOfWork())
		{
			noChangesAfterCycle = true;
		}
	}

	return noChangesAfterCycle;
}

void Solution::printToConsoleDifferences(const Solution& copy, Color color) const
{
	pict.printToConsoleDifferences(copy.pict, color);
	std::cout << "\n";

	for (size_t i = 0; i < conditions.size(); ++i)
	{
		for (size_t j = 0; j < conditions[i].size(); ++j)
		{
			std::cout << i << " " << j << ": ";
			conditions[i][j].printToConsoleDifferences(copy.conditions[i][j], color);
		}
	}
}

std::string Solution::pictToString() const
{
	return pict.toString();
}

std::string Solution::conditionsToString() const
{
	std::string answer;

	for (size_t i = 0; i < conditions.size(); ++i)
	{
		for (size_t j = 0; j < conditions[i].size(); ++j)
		{
			answer.append(std::to_string(i) + " " + std::to_string(j) + ": ");
			answer.append(conditions[i][j].toString());
		}
	}

	return answer;
}
