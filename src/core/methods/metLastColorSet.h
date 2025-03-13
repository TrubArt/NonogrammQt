#ifndef METHOD_LASTCOLORSET_NONOGRAM
#define METHOD_LASTCOLORSET_NONOGRAM

#include "iMethod.h"

class LastColorSet : public IMethod
{
public:
	void realization(const Condition& cond, Picture& pict, CellQueue& queue, bool isColumn, size_t rowOrColIndex) const override;
	std::string methodName() const override;
	std::string principleOfMethodWork() const override;
};

#endif // !METHOD_LASTCOLORSET_NONOGRAM
