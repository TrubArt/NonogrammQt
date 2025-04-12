#include <memory>
#include <QMessageBox>
#include <QErrorMessage>

#include "mainwindow.h"
#include "core/filesWork/loadManagerCpp.h"
#include "levelChangeDialog/levelchangedialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindowClass)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowState::WindowMaximized);
    setWindowTitle(tr("NonogrammSolver"));

    viewInitialization();
    m_levelsStorage.loadLevels();

    connectInitialization();
}

void MainWindow::viewInitialization()
{
    m_view.setParent(this);
    ui->gridLayout->addWidget(&m_view, 0, 1, 1, 1);
    m_view.setScene(m_picture.get());
}

void MainWindow::connectInitialization()
{
    // actions
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::actionExit);
    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::actionStartSolution);
    connect(ui->actionChangeLevel, &QAction::triggered, this, &MainWindow::actionChangeLevel);
    connect(ui->actionResetPicture, &QAction::triggered, this, &MainWindow::actiontResetTableCells);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintCell(const PaintCellInfo& cellInfo)
{
    int hIndex = cellInfo.rowNumber;
    int wIndex = cellInfo.indexInRow;

    m_picture.repaintCell(hIndex, wIndex, cellInfo.color);
}

void MainWindow::changeNonogram(const QString& lvlName)
{
    std::shared_ptr<LevelData> data = m_levelsStorage.getLevelData(lvlName);
    if (!data)
    {
        QErrorMessage(this).showMessage(tr("The selected level does not exist!"));
    }

    m_currentLevelName = lvlName;
    m_picture.setColors(data->properties.colors);

    mp_currSolution = Solution(m_levelsStorage.getManager(lvlName));
    data->isLoadedDataInformation = true;

    // отрисовка нового изображения
    const Picture& pict = mp_currSolution->getPicture();
    m_picture.repaintTable(pict.getRowCount(), pict.getColumnCount());

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
    if (!mp_currSolution || m_currentLevelName.isEmpty())
    {
        QMessageBox msgChange;
        msgChange.setWindowTitle(tr("Hint"));
        msgChange.setText(tr("Select a level before starting the solution!"));
        msgChange.exec();

        actionChangeLevel();
        return;
    }

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
    std::unique_ptr<LevelChangeDialog> lvlChangeDlg = std::make_unique<LevelChangeDialog>
        (m_currentLevelName
        , m_levelsStorage.getData());

    if (lvlChangeDlg->exec())
    {
        const QMap<QString, PropertiesInformation>& newProperties = lvlChangeDlg->getProperties();
        for (auto it = newProperties.begin(); it != newProperties.end(); ++it)
        {
            // проверка на случай изменения имени уровня внутри диалога. В данный момент такое действие не обрабатывается
            Q_ASSERT_X(m_levelsStorage.getLevelsList().contains(it.value().name), "MainWindow::actionChangeLevel", "name didnt Exist");
            m_levelsStorage.setProperties(it.value().name, it.value());
        }

        changeNonogram(lvlChangeDlg->getChosenLevelName());
    }
}

void MainWindow::actionSaveLevels()
{

}
