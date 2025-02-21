#include "solution.h"
#include "fileLoader.h"
#include "methods/metLastColorSet.h"
#include "methods/metStartEndNum.h"

Solution::Solution(const std::string& fileCondition, const std::string& fileAdditCondit)
{
	// enum для обращения к строкам/столбцам в conditions
	enum LineClassifier { row, col };

	FileLoader cond(fileCondition);

	std::vector<int> tmp;

	// получение данных о размере изображения
	tmp = cond.getNumbersSequence();
	size_t sizeN = tmp[0];
	size_t sizeM = tmp[1];

	pict = Picture(sizeN, sizeM);
	conditions[row].resize(sizeN);
	conditions[col].resize(sizeM);

	// сначала добавление доп. цветов
	FileLoader f2(fileAdditCondit);
	while (!f2.isEmpty())
	{
		tmp = f2.getNumbersSequence();
		if (!tmp.empty())
		{
			pict.setColor(tmp[0], tmp[1], static_cast<CellType>(tmp[2]));
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

void Solution::callingMethods(const std::vector<IMethod*>& methods)
{
	//// копия, с которой будет сравниваться *this для вывода изменений в консоль
	Solution copy = *this;

	// цикл с прогоном всех методов
	for (const auto& i : methods)
	{
		// двойной цикл для прохода по всем строкам/столбцам
		for (size_t rowOrCol = 0; rowOrCol < conditions.size(); ++rowOrCol)
		{
			for (size_t positionInRowOrCol = 0; positionInRowOrCol < conditions[rowOrCol].size(); ++positionInRowOrCol)
			{
				Condition& curentCond = conditions[rowOrCol][positionInRowOrCol];

				if (curentCond.getIsFullFlag())		// если строка уже завершена
				{
					continue;
				}

				// вызов определённого метода					
				i->realization(curentCond, &pict, std::make_pair(rowOrCol, positionInRowOrCol));

				// метод по определению числа с края строки
				StartEndNum().realization(curentCond, &pict, std::make_pair(rowOrCol, positionInRowOrCol));

				// изменение данных о строке после цикла
				UpdCondReturnParam updPar = curentCond.updateCondition();
				if (updPar != UpdCondReturnParam::lineNotCompleted)	// если строка закончена, то однозначно закрашиваем оставшиеся поля
				{
					LastColorSet().anotrealization(curentCond, &pict, std::make_pair(rowOrCol, positionInRowOrCol), updPar);
				}

			}
		}

		// вывод в консоль изменений после работы метода

		std::cout << "\nИзменения после работы метода" << i->methodName() << ":\n\n";
		this->printToConsoleDifferences(copy, 4);

		copy = *this;
	}
}

void Solution::printToConsoleDifferences(const Solution& copy, int color) const
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
