#ifndef METHOD_UNAMBIGUOUSBLACK_NONOGRAM
#define METHOD_UNAMBIGUOUSBLACK_NONOGRAM

#include "iMethod.h"

// определяет 100% CellType::black в центре диапазона каждого числа
class UnambiguousBlack : public IMethod
{
public:
	void realization(const Condition& cond, Picture* pict, const std::pair<int, int>& posit) const override;
	std::string methodName() const override;
	std::string principleOfMethodWork() const override;
};

#endif // !METHOD_UNAMBIGUOUSBLACK_NONOGRAM
