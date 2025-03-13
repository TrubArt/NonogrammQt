#ifndef ILOADMANAGER_NONOGRAM
#define ILOADMANAGER_NONOGRAM

#include <utility>
#include <vector>
#include <string>

// интерфейс для менеджера над загрузчиком информации из файла
class ILoadManager
{
protected:
	std::string directory;
	std::vector<std::string> files;

	std::string directoryDelimeter = "\\";

public:
	ILoadManager(const std::string& directory, const std::vector<std::string>& files);
	virtual ~ILoadManager() = default;

	virtual std::pair<size_t, size_t> getNonogramSize() = 0;
	virtual std::vector<std::vector<size_t>> getAdditionalCondition() = 0;
	virtual std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) = 0;
};

#endif // !ILOADMANAGER_NONOGRAM
