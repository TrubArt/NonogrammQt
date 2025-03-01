#include "cellQueue.h"

std::vector<PaintCellInfo>& CellQueue::get()
{
	return data;
}

const std::vector<PaintCellInfo>& CellQueue::get() const
{
	return data;
}

void CellQueue::customPush(const PaintCellInfo& el)
{
	data.push_back(el);
}
