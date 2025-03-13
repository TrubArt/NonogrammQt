#ifndef IFILELOADER_NONOGRAM
#define IFILELOADER_NONOGRAM

#include <string>
#include <utility>
#include <vector>

// интерфейс для загрузчиков информации о нонограмме из файла
class iFileLoader
{
public:
	virtual ~iFileLoader() = default;

	virtual void setFile(const std::string& fileName) = 0;
	virtual std::string getFileName() const = 0;

	virtual std::pair<size_t, size_t> getNonogramSize() = 0;
	virtual std::vector<std::vector<size_t>> getAdditionalCondition() = 0;
	virtual std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) = 0;
};

#endif // !IFILELOADER_NONOGRAM
