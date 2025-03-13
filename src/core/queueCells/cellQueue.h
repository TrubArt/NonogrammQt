#ifndef CELLQUEUE_NONOGRAM
#define CELLQUEUE_NONOGRAM

#include "paintCellInfo.h"

#include <vector>

// класс, иммитирующий очередь из закрашенных клеток в изображении
class CellQueue
{
	std::vector<PaintCellInfo> data;

public:
	CellQueue() = default;
	std::vector<PaintCellInfo>& get();
	const std::vector<PaintCellInfo>& get() const;

	// не надо класть с помощью данного метода
	// элементы из вектора в связи с реалокацией :)
	void customPush(const PaintCellInfo& el);
};

#endif // !CELLQUEUE_NONOGRAM
