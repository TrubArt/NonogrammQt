#include "mainwindow.h"
#include "solution.h"
#include "methods/methodsVectorShell.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::string directoryPath = "C:\\Users\\user\\Qttest\\Nonogramm\\levels\\2";
    Solution maintask(directoryPath + "\\Condition", directoryPath + "\\Additional color condition");

    std::cout << "Picture before:\n";
    std::cout << maintask.getPicture();

    bool earlyCycleOut = maintask.nonogramSolution();

    // обработка причины прекращения цикла
    if (earlyCycleOut)
    {
        std::cout << "\nPicture dont finish:(\n";
    }

    std::cout << "Finaly picture:\n";
    maintask.getPicture().printToConsoleColor(Color::black, Color::darkBlue);
    std::cin.get();

    std::vector<PaintCellInfo> cells = maintask.getQueue().get();
    std::cout << "Cells queue:\n";

    size_t index = 0;
    for (const auto& cell : cells)
    {
        // std::cout << ++index << ": ";
        // std::cout << cell.rowNumber << " ";
        // std::cout << cell.indexInRow << " ";
        // std::cout << static_cast<int>(cell.color);
        // std::cout << "\n";
        w.paintCell(cell);
    }

    return a.exec();
}
