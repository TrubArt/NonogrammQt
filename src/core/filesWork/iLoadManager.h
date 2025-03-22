#ifndef ILOADMANAGER_NONOGRAM
#define ILOADMANAGER_NONOGRAM

#include <utility>
#include <vector>
#include <array>
#include <string>

// интерфейс для менеджера над загрузчиком информации из файла
class ILoadManager
{
public:
	virtual ~ILoadManager() = default;

	virtual std::pair<size_t, size_t> getNonogramSize() = 0;
	virtual std::vector<std::array<size_t, 3>> getAdditionalCondition() = 0;
	virtual std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) = 0;
};

#endif // !ILOADMANAGER_NONOGRAM
