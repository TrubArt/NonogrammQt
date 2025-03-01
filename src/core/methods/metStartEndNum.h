#ifndef METHOD_STARTENDNUM_NONOGRAM
#define METHOD_STARTENDNUM_NONOGRAM

#include "iMethod.h"

// если start || end == CellType::black, то однозначно закрашивает клетки принадлежащие первому/последнему числу
class StartEndNum : public IMethod
{
public:
	void realization(const Condition& cond, Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex) const override;
	std::string methodName() const override;
	std::string principleOfMethodWork() const override;
};

#endif // !METHOD_STARTENDNUM_NONOGRAM
