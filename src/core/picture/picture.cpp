#include "picture.h"

namespace
{
	// функция нужна для проверки синхронизации строк и столбцов
	bool checkSynchronization(const std::vector<Line*>& rows, const std::vector<Line*>& columns)
	{
		for (size_t i = 0; i < rows.size(); ++i)
		{
			for (size_t j = 0; j < columns.size(); ++j)
			{
				if (rows[i]->getCellType(j) != columns[j]->getCellType(i))
				{
					return false;
				}
			}
		}

		return true;
	} // на релизе убрать
}

Picture::Picture(size_t rowCount, size_t colCount)
{
	rows.resize(rowCount);
	columns.resize(colCount);

	for (auto& i : rows)
	{
		i = new Line(colCount);
	}
	for (auto& i : columns)
	{
		i = new Line(rowCount);
	}
}

Picture::Picture(const Picture& x)
{
	rows.resize(x.rows.size());
	columns.resize(x.columns.size());

	for (size_t i = 0; i < rows.size(); ++i)
	{
		rows[i] = new Line(*x.rows[i]);
	}
	for (size_t i = 0; i < columns.size(); ++i)
	{
		columns[i] = new Line(*x.columns[i]);
	}
}

Picture::~Picture()
{
	for (auto& i : rows)
	{
		delete i;
	}
	for (auto& i : columns)
	{
		delete i;
	}
}

Picture& Picture::operator=(const Picture& x)
{
	if (&x != this)
	{

		// предварительная очистка памяти
		for (auto& i : rows)
		{
			if (i)
			{
				delete i;
			}
		}
		for (auto& i : columns)
		{
			if (i)
			{
				delete i;
			}
		}

		rows.resize(x.rows.size());
		columns.resize(x.columns.size());

		for (size_t i = 0; i < rows.size(); ++i)
		{
			rows[i] = new Line(*x.rows[i]);
		}
		for (size_t i = 0; i < columns.size(); ++i)
		{
			columns[i] = new Line(*x.columns[i]);
		}
	}

	return *this;
}

bool Picture::operator==(const Picture& x) const
{
	for (size_t i = 0; i < rows.size(); ++i)
	{
		if (*rows[i] != *x.rows[i])
		{
			return false;
		}
	}

	return true;
}

bool Picture::operator!=(const Picture& x) const
{
	return !(*this == x);
}

const Line* Picture::getPtr(const std::pair<size_t, size_t>& x) const
{
	return x.first == 0 ? rows[x.second] : columns[x.second];
}

bool Picture::setColor(size_t rowNumber, size_t index, CellType cType)
{
	if (!needChanges(rowNumber, index, cType))
	{
		return false;
	}

	paint(rowNumber, index, cType);
	return true;
}

void Picture::printToConsoleDifferences(const Picture& pict, Color color) const
{
	if (pict.rows.size() != rows.size() || pict.columns.size() != columns.size())
	{
		std::cout << "Error in Picture::printToConsoleDifferences. Different picture sizes\n";
		return;
	}

	for (size_t strNum = 0; strNum < rows.size(); ++strNum)
	{
		rows[strNum]->printToConsoleDifferences(*pict.rows[strNum], color);
		std::cout << "\n";
	}
}

void Picture::printToConsoleColor(Color whiteColor, Color blackColor) const
{
	for (size_t strNum = 0; strNum < rows.size(); ++strNum)
	{
		rows[strNum]->printToConsoleColor(whiteColor, blackColor);
		std::cout << "\n";
	}
}

std::string Picture::toString() const
{
	std::string answer;
	for (const auto& i : rows)
	{
		answer.append(i->toString() + "\n");
	}
	return answer;
}

std::ostream& operator<<(std::ostream& out, const Picture& pict)
{
	out << pict.toString();
	return out;
}

bool Picture::needChanges(size_t rowNumber, size_t index, CellType cType) const
{
	if (!checkSynchronization(rows, columns))
	{
		std::cerr << "Picture synchronization failed!!!\n";
		std::exit(1);
	}

	enum NeedToDraw { no, yes };
	CellType cellColor = rows[rowNumber]->getCellType(index);

	if (cellColor == CellType::undefined)
	{
		return NeedToDraw::yes;
	}

	// обработка ситуации, если клетка уже закрашена
	if (cellColor == cType)
	{
		return NeedToDraw::no;
	}

	std::cerr << "Repainting of an already painted cell!!!\n";
	std::exit(1);

	return NeedToDraw::no;
}

void Picture::paint(size_t rowNumber, size_t index, CellType cType)
{
	// необходимо 2 вызова, чтобы была однозначная картинка
	// и с точки зрения строк и с точки зрения столбцов
	rows[rowNumber]->setCellType(index, cType);
	columns[index]->setCellType(rowNumber, cType);
}
