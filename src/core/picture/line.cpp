#include "line.h"

#include <algorithm>

Line::Line(size_t size)
{
	data.resize(size);
	for (auto& i : data)
	{
		i = new Cell();
	}
}

Line::Line(const Line& x)
{
	data.resize(x.data.size());

	for (size_t i = 0; i < data.size(); ++i)
	{
		data[i] = new Cell(x.data[i]->get());
	}
}

Line::~Line()
{
	for (const auto& i : data)
	{
		delete i;
	}
}

Line& Line::operator=(const Line& x)
{
	if (&x != this)
	{
		for (const auto& i : data) // предварительно освобождается память
		{
			if (i)
			{
				delete i;
			}
		}

		data.resize(x.data.size());

		for (size_t i = 0; i < data.size(); ++i)
		{
			data[i] = new Cell(x.data[i]->get());
		}
	}

	return *this;
}

bool Line::operator==(const Line& x) const
{
	if (data.size() != x.data.size())
	{
		return false;
	} 

	for (size_t i = 0; i < data.size(); ++i)
	{
		if (data[i]->get() != x.data[i]->get())
		{
			return false;
		}
	}

	return true;
}

bool Line::operator!=(const Line& x) const
{
	return !(*this == x);
}

void Line::setCellType(size_t index, CellType cType)
{
	data[index]->set(cType);
}

CellType Line::getCellType(size_t index) const
{
	return data[index]->get();
}

size_t Line::getSize() const
{
	return data.size();
}

size_t Line::getCountTypeCell(CellType cType) const
{
	//return std::count_if(data.begin(), data.end(), [cType](Cell* x) { return x->get() == cType ? true : false; });
	return getCountTypeCell(0, data.size(), cType);
}

size_t Line::getCountTypeCell(size_t startIndex, size_t endIndex, CellType cType) const
{
	size_t answer = 0;
	if (endIndex > data.size())
	{
		std::cout << "Out of Line\n";
		return answer;
	}

	for (size_t i = startIndex; i < endIndex; ++i)
	{
		if (data[i]->get() == cType)
		{
			++answer;
		}
	}

	return answer;
}

int Line::getLeftIndexTypeCell(size_t startIndex, size_t endIndex, CellType cType) const
{
	int answer = -1;
	if (endIndex > data.size())
	{
		std::cout << "Out of Line\n";
		return answer;
	}

	for (size_t i = startIndex; i < endIndex; ++i)
	{
		if (data[i]->get() == cType)
		{
			return i;
		}
	}

	return answer;
}

int Line::getRightIndexTypeCell(size_t startIndex, size_t endIndex, CellType cType) const
{
	int answer = -1;
	if (endIndex == 0 || endIndex > data.size())
	{
		std::cout << "Out of Line\n";
		return answer;
	}

	int iStartIndex = static_cast<int>(startIndex);
	for (int i = endIndex - 1; i >= iStartIndex; --i)
	{
		if (data[i]->get() == cType)
		{
			return i;
		}
	}

	return answer;
}

void Line::printToConsoleDifferences(const Line& line, Color color) const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD lightDifferens = static_cast<WORD>(color);
	WORD undefinedColor = static_cast<WORD>(Color::white);

	for (size_t index = 0; index < data.size(); ++index)
	{
		if (data[index]->get() != line.data[index]->get())
		{
			SetConsoleTextAttribute(console, lightDifferens);
		}
		std::cout << " " << data[index]->toString();

		SetConsoleTextAttribute(console, undefinedColor);
	}
}

void Line::printToConsoleColor(Color whiteColor, Color blackColor) const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD undefinedColor = static_cast<WORD>(Color::white);
	WORD whiteColorw = static_cast<WORD>(whiteColor);
	WORD blackColorw = static_cast<WORD>(blackColor);

	for (size_t index = 0; index < data.size(); ++index)
	{
		if (data[index]->get() == CellType::black)
		{
			SetConsoleTextAttribute(console, blackColorw);
		}
		if (data[index]->get() == CellType::white)
		{
			SetConsoleTextAttribute(console, whiteColorw);
		}
		std::cout << " " << data[index]->toString();

		SetConsoleTextAttribute(console, undefinedColor);
	}
}

std::string Line::toString() const
{
	std::string answer;
	for (const auto& i : data)
	{
		answer.append(" " + i->toString());
	}

	return answer;
}

std::ostream& operator<<(std::ostream& out, const Line& line)
{
	out << line.toString();
	return out;
}
