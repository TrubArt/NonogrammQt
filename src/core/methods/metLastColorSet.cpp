#include "metLastColorSet.h"

void LastColorSet::realization(const Condition& cond, Picture* pict, const std::pair<int, int>& posit) const
{}

std::string LastColorSet::methodName() const
{
	return "LastColorSet";
}

std::string LastColorSet::principleOfMethodWork() const
{
	std::string answ;
	answ.append("Метод принимает на вход UpdCondReturnParam param, который сообщает классу о том, что\n");
	answ.append("необходимо все оставшиеся в линии CellType::undefined закрасить в цвет param");
	return answ;
}

void LastColorSet::anotrealization(const Condition& cond, Picture* pict, const std::pair<int, int>& posit, UpdCondReturnParam param) const
{
	if (param == UpdCondReturnParam::lineNotCompleted)
	{
		return;
	}

	const Line* analyzedLine = cond.getLinePtr();
	for (int i = cond.getStart(); i < cond.getEnd(); ++i)
	{
		if (analyzedLine->getCellType(i) == CellType::undefined)
		{
			this->setColorWithInformation(pict, posit, i, static_cast<CellType>(param));
		}
	}
}
