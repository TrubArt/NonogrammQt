#ifndef METHODSVECTORSHELL_NONOGRAM
#define METHODSVECTORSHELL_NONOGRAM

#include "iMethod.h"

#include <vector>

class MethodsVectorShell
{
	std::vector<IMethod*> list;

public:

	// ctor, dtor, operators

	// для добавления новых методов нужно изменить конструктор по умолчанию MethodsVectorShell
	// считаю такое решение приемлимым. Если нужно будет изменить порядок вызова методов, то
	// всегда можно дописать методы для работы с этим классом
	MethodsVectorShell();
	~MethodsVectorShell();

	// functions

	void clear();
	void pushMehod(IMethod* x);
	const std::vector<IMethod*>& get() const;
};

#endif // !METHODSVECTORSHELL_NONOGRAM
