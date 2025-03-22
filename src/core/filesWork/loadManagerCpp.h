#ifndef LOADMANGERCPP_NONOGARAM
#define LOADMANGERCPP_NONOGARAM

#include "iLoadManager.h"
#include "iFileLoader.h"

#include <memory>

// менеджер работы с файлами на основе класса FileLoaderCpp
class LoadManagerCpp : public ILoadManager
{
	std::unique_ptr<iFileLoader> fileLoader;

public:
	LoadManagerCpp(const std::string& directory, const std::vector<std::string>& files);

	std::pair<size_t, size_t> getNonogramSize() override;
	std::vector<std::array<size_t, 3>> getAdditionalCondition() override;
	std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) override;
};

#endif // !LOADMANGERCPP_NONOGARAM
