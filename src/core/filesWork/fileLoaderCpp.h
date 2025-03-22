#ifndef FILELOADERCPP_NONOGRAM
#define FILELOADERCPP_NONOGRAM

#include "iFileLoader.h"

#include <fstream>
#include <string>
#include <vector>

// класс, необходимый для загрузки условия нонограммы из файла в Picture
class FileLoaderCpp : public iFileLoader
{
	std::string fileName;	// имя файла к которому привязан поток
	std::ifstream file;		// поток с файлом

	const std::string suf = ".txt";

public:
	// ctors, dtor, operators

	FileLoaderCpp() = default;
	FileLoaderCpp(const std::string& fileName);
	~FileLoaderCpp() override;

	void setFile(const std::string& fileName) override;
	std::string getFileName() const override;

	std::vector<std::array<size_t, 3>> getAdditionalCondition() override;
	std::pair<size_t, size_t> getNonogramSize() override;

	// возвращает vector c последовательностью чисел из строки
	std::vector<size_t> getLineSequence(bool isColumn, size_t lineIndex) override;

	// возвращает true, если читать из потока больше нечего
	bool isEndOfFile() const;

private:
	// возвращает первое число из str начиная с index
	size_t getNumber(const std::string& str, size_t& index) const;

	// возвращает первую непустую строку файла
	// если таковых нет вернёт пустую строку
	std::string skipEmptyFileLine();
};
#endif // !FILELOADERCPP_NONOGRAM
