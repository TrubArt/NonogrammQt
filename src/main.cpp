#include "mainwindow.h"
#include "solution.h"
#include "methods/methodsVectorShell.h"

#include <QApplication>

bool nonogramSolution(Solution& maintask, const std::vector<IMethod*>& methods)
{
    bool noChangesAfterCycle = false;

    while (!noChangesAfterCycle && !maintask.isEndOfWork())
    {
        Picture pictureToCompare{ maintask.getPicture() };

        // работа методов
        maintask.callingMethods(methods);

        // если после работы методов нет изменений
        if (pictureToCompare == maintask.getPicture() && !maintask.isEndOfWork())
        {
            noChangesAfterCycle = true;
        }
    }

    return noChangesAfterCycle;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::string directoryPath = "C:\\Users\\user\\Qttest\\Nonogramm";
    Solution maintask(directoryPath + "\\Condition", directoryPath + "\\Additional color condition");

    // для добавления новых методов нужно изменить конструктор по умолчанию MethodsVectorShell
    // считаю такое решение приемлимым. Если нужно будет изменить порядок вызова методов, то
    // всегда можно дописать методы для работы с этим классом
    MethodsVectorShell vect;

    bool earlyCycleOut = nonogramSolution(maintask, vect.get());

    // обработка причины прекращения цикла
    if (earlyCycleOut)
    {
        std::cout << "\nPicture dont finished:(\n";
    }

   std::cout << "Finaly picture:\n";
    maintask.getPicture().printToConsoleColor(0, 1);

    return a.exec();
}
