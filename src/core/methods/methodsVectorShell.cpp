#include "methodsVectorShell.h"
#include "metUnambiguousBlack.h"
#include "metUnambiguousWhite.h"

MethodsVectorShell::MethodsVectorShell()
{
	methods.push_back(new UnambiguousBlack());
	methods.push_back(new UnambiguousWhite());
}

MethodsVectorShell::~MethodsVectorShell()
{
	for (auto& i : methods)
	{
		delete i;
	}
}

void MethodsVectorShell::clear()
{
	methods.clear();
}

void MethodsVectorShell::pushMehod(IMethod* x)
{
	methods.push_back(x);
}

const std::vector<IMethod*>& MethodsVectorShell::get() const
{
	return methods;
}
