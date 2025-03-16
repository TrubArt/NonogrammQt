#include <memory>

#include "mainwindow.h"
#include "core/filesWork/loadManagerCpp.h"
#include "levelChangeDlg/levelchangedialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindowClass)
    , m_picture()
    , mp_currSolution(nullptr)
{
    ui->setupUi(this);
    m_view.setParent(this);

    setWindowState(Qt::WindowState::WindowMaximized);

    ui->gridLayout->addWidget(&m_view, 0, 1, 1, 1);

    m_view.setScene(m_picture.get());

    connectInitialization();
}

void MainWindow::connectInitialization()
{
    connect(this, &MainWindow::changeNon, this, &MainWindow::changeNonogram);

    // actions
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::actionExit);
    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::actionStartSolution);
    connect(ui->actionChangeLevel, &QAction::triggered, this, &MainWindow::actionChangeLevel);
    connect(ui->actionResetPicture, &QAction::triggered, this, &MainWindow::actiontResetTableCells);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (mp_currSolution)
    {
        delete mp_currSolution;
    }
}

void MainWindow::paintCell(const PaintCellInfo& cellInfo)
{
    int hIndex = cellInfo.rowNumber;
    int wIndex = cellInfo.indexInRow;

    m_picture.repaintCell(hIndex, wIndex, cellInfo.color);
}

void MainWindow::repaintTable(int rowCount, int columnCount)
{
    m_picture.repaintTable(rowCount, columnCount);
}

void MainWindow::changeNonogram()
{
    if (mp_currSolution)
    {
        delete mp_currSolution;
    }

    // ***************************** инициализация loader с нужными файлами из директории ******************

    // .txt к названию добавляется в FileLoaderCpp
    std::vector<std::string> files = { "additional color condition", "condition", "info" };
    std::string directoryPath = "C:\\Users\\user\\Qttest\\Nonogramm\\levels\\3";
    LoadManagerCpp loadManager(directoryPath, files);

    // *****************************************************************************************************

    mp_currSolution = new Solution(loadManager);

    // отрисовка нового изображения
    const Picture& pict = mp_currSolution->getPicture();
    repaintTable(pict.getRowCount(), pict.getColumnCount());

    // добавление на рисунок клеток из additionColor.txt
    drawCellsFromQueue();
}

void MainWindow::actiontResetTableCells()
{
    m_picture.resetTableCells();
}

void MainWindow::drawCellsFromQueue()
{
    const std::vector<PaintCellInfo>& cells = mp_currSolution->getQueue().get();
    for (const PaintCellInfo& cell : cells)
    {
        paintCell(cell);
    }
}

void MainWindow::actionExit()
{
    QApplication::quit();
}

void MainWindow::actionStartSolution()
{
    //emit changeNon();

    bool earlyCycleOut = mp_currSolution->nonogramSolution();

    // обработка причины прекращения цикла
    if (earlyCycleOut)
    {
        ui->statusBar->showMessage(tr("Picture dont finish:("));
    }
    else
    {
        ui->statusBar->showMessage(tr("Picture successfully finished"));
    }

    // добавление на рисунок полученного решения
    drawCellsFromQueue();
}

void MainWindow::actionChangeLevel()
{
    std::unique_ptr<LevelChangeDialog> lvlChangeDlg = std::make_unique<LevelChangeDialog>();
    if (lvlChangeDlg->exec())
    {
        emit changeNon();
    }
}
