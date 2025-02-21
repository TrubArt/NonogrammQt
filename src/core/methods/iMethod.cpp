#include "iMethod.h"

void IMethod::setColorWithInformation(Picture* pict, const std::pair<int, int>& posit, int index, CellType cType) const
{
	if (posit.first == 0)
	{
		pict->setColor(posit.second, index, cType);
	}
	else
	{
		pict->setColor(index, posit.second, cType);
	}
}
