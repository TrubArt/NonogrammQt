#ifndef IFILELOADER_NONOGRAM
#define IFILELOADER_NONOGRAM

#include <string>
#include <utility>
#include <array>
#include <vector>

// интерфейс для загрузчиков информации о нонограмме из файла
class iFileLoader
{
public:
	virtual ~iFileLoader() = default;

	virtual void setFile(const std::string& fileName) = 0;
	virtual std::string getFileName() const = 0;

	virtual std::pair<size_t, size_t> getNonogramSize() = 0;
	virtual std::vector<std::array<size_t, 3>> getAdditionalCondition() = 0;
	virtual std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) = 0;
};

#endif // !IFILELOADER_NONOGRAM
