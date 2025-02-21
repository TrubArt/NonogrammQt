#include "metUnambiguousBlack.h"

void UnambiguousBlack::realization(const Condition& cond, Picture* pict, const std::pair<int, int>& posit) const
{
	const std::list<NumberAndBorders>& list = cond.getNumInfo();
	for(const auto& element : list)
	{ 
		for (int index = element.getD().second - element.getNum(); index < element.getD().first + element.getNum(); ++index)
		{
			this->setColorWithInformation(pict, posit, index, CellType::black);
		}
	}
}

std::string UnambiguousBlack::methodName() const
{
	return "UnambiguousBlack";
}

std::string UnambiguousBlack::principleOfMethodWork() const
{
	std::string answ;
	answ.append("Проходится по всем незаконченным числам в линии. Работает с диапазоном(D).\n");
	answ.append("Определяет чёрные клетки, которые однозначно можно закрасить, путём наложения числа относительно начала и конца диапазона(D).\n");
	answ.append("Закрашивает клетки, которые принадлежат числу и в первом и втором случае");
	return answ;
}
