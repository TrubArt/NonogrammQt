#ifndef METHODSVECTORSHELL_NONOGRAM
#define METHODSVECTORSHELL_NONOGRAM

#include "iMethod.h"

#include <vector>

class MethodsVectorShell
{
	std::vector<IMethod*> methods;

public:

	// ctor, dtor, operators

	MethodsVectorShell();
	MethodsVectorShell(const MethodsVectorShell&) = delete;
	~MethodsVectorShell();
	MethodsVectorShell& operator=(const MethodsVectorShell&) = delete;

	// functions

	void clear();
	void pushMehod(IMethod* x);
	const std::vector<IMethod*>& get() const;
};

#endif // !METHODSVECTORSHELL_NONOGRAM
