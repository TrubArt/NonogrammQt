#ifndef METHOD_UNAMBIGUOUSWHITE_NONOGRAM
#define METHOD_UNAMBIGUOUSWHITE_NONOGRAM

#include "iMethod.h"

// определяет 100% CellType::white
class UnambiguousWhite : public IMethod
{
public:
	void realization(const Condition& cond, Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex) const override;
	std::string methodName() const override;
	std::string principleOfMethodWork() const override;
};

#endif // !METHOD_UNAMBIGUOUSWHITE_NONOGRAM
