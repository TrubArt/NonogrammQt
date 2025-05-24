#include "methodsVectorShell.h"
#include "metUnambiguousBlack.h"
#include "metUnambiguousWhite.h"

MethodsVectorShell::MethodsVectorShell()
{
	list.push_back(new UnambiguousBlack());
	list.push_back(new UnambiguousWhite());
}

MethodsVectorShell::~MethodsVectorShell()
{
    clear();
}

void MethodsVectorShell::clear()
{
    for (auto& i : list)
    {
        delete i;
    }
	list.clear();
}

void MethodsVectorShell::pushMehod(IMethod* x)
{
	list.push_back(x);
}

const std::vector<IMethod*>& MethodsVectorShell::get() const
{
	return list;
}
