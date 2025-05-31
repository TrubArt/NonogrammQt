#include "solution.h"
#include "methods/metLastColorSet.h"
#include "methods/metStartEndNum.h"

const MethodsVectorShell Solution::methods = MethodsVectorShell();

Solution::Solution(ILoadManager& loader)
{
	// получение данных о размере изображения
	auto nonSize = loader.getNonogramSize();
	size_t rowCount = nonSize.first;
	size_t colCount = nonSize.second;

	pict = Picture(rowCount, colCount);
    conditions[row].resize(rowCount);
    conditions[col].resize(colCount);

	// сначала добавление изначально заданных клеток
	auto addCond = loader.getAdditionalCondition();
	for (const auto& condition : addCond)
	{
		PaintCellInfo cellInfo(condition[0], condition[1], static_cast<CellType>(condition[2]));
        bool isPaint = false;

        try
        {
            isPaint = pict.setColor(cellInfo.rowNumber, cellInfo.indexInRow, cellInfo.color);
        }
        catch (const std::logic_error&)
        {
            isPaint = false;
        }

        if (isPaint)
		{
			queue.customPush(cellInfo);
		}
	}

	// потом получение данных о строках и столбцах
	for (size_t i = 0; i < rowCount; ++i)
	{
        std::pair<size_t, size_t> lineDestination = std::make_pair(row, i);
		const Line* line = pict.getPtr(lineDestination);

        conditions[row][i] = Condition(line->getSize(), line, loader.getLineSequence(row, i));
	}
	for (size_t i = 0; i < colCount; ++i)
	{
        std::pair<size_t, size_t> lineDestination = std::make_pair(col, i);
		const Line* line = pict.getPtr(lineDestination);

        conditions[col][i] = Condition(line->getSize(), line, loader.getLineSequence(col, i));
	}
}

Solution::Solution(const Solution& other)
    : pict(other.pict)
    , conditions(other.conditions)
    , queue(other.queue)
{
    for (size_t i = 0; i < pict.getRowCount(); ++i)
    {
        std::pair<size_t, size_t> lineDestination = std::make_pair(row, i);
        const Line* line = pict.getPtr(lineDestination);

        conditions[row][i].setLinePtr(line);
    }
    for (size_t i = 0; i < pict.getColumnCount(); ++i)
    {
        std::pair<size_t, size_t> lineDestination = std::make_pair(col, i);
        const Line* line = pict.getPtr(lineDestination);

        conditions[col][i].setLinePtr(line);
    }
}

Solution& Solution::operator=(const Solution& other)
{
    if (&other != this)
    {
        pict = other.pict;
        conditions = other.conditions;
        queue = other.queue;

        for (size_t i = 0; i < pict.getRowCount(); ++i)
        {
            std::pair<size_t, size_t> lineDestination = std::make_pair(row, i);
            const Line* line = pict.getPtr(lineDestination);

            conditions[row][i].setLinePtr(line);
        }
        for (size_t i = 0; i < pict.getColumnCount(); ++i)
        {
            std::pair<size_t, size_t> lineDestination = std::make_pair(col, i);
            const Line* line = pict.getPtr(lineDestination);

            conditions[col][i].setLinePtr(line);
        }
    }

    return *this;
}

const Picture& Solution::getPicture() const
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

const CellQueue& Solution::getQueue() const
{
	return queue;
}

void Solution::callingMethods()
{
	// копия, с которой будет сравниваться *this для вывода изменений в консоль
    // Solution copy = *this;

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

        //std::cout << "\nChanges after " << method->methodName() << " method work:\n\n";
        //printToConsoleDifferences(copy, Color::crimson);

        // copy = *this;
	}
}

Solution::ReturnStatus Solution::nonogramSolution()
{
	bool noChangesAfterCycle = false;

    try
    {
        while (!noChangesAfterCycle && !isEndOfWork())
        {
            Picture pictureToCompare{ pict };

            // работа методов
            callingMethods();

            // если после работы методов нет изменений
            if (pictureToCompare == pict && !isEndOfWork())
            {
                noChangesAfterCycle = true;
            }
        }
    }
    catch (const std::logic_error&)
    {
        return ReturnStatus::IncorrectInputData;
    }

    return static_cast<ReturnStatus>(noChangesAfterCycle);
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
