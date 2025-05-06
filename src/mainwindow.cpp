#include <memory>
#include <QMessageBox>
#include <QErrorMessage>

#include "mainwindow.h"
#include "core/filesWork/loadManagerCpp.h"
#include "levelChangeDialog/levelchangedialog.h"
#include "levelCreate/conditionlevelcreate.h"

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
    connect(ui->actionWriteConditions, &QAction::triggered, this, &MainWindow::actionCondionsLevelCreate);
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
    drawCellsFromQueue(mp_currSolution->getQueue().get());
}

void MainWindow::actiontResetTableCells()
{
    // Если после вызова этой функции заново запустить решение, на самом деле ничего пересчитываться не будет
    // Отрисуются уже посчитанные клетки из queue. Возможно стоит переделать,
    // тк может ввести в заблуждение при дальнейшей разработке
    m_picture.resetTableCells();

    // отрисовка клеток из additionColor
    std::shared_ptr<LevelData> data = m_levelsStorage.getLevelData(m_currentLevelName);
    if (!data || !data->isLoadedDataInformation)
    {
        return;
    }

    CellQueue queue;
    for (const std::array<size_t, 3>& additionInfo : data->data.additionConditions)
    {
        queue.customPush(PaintCellInfo(additionInfo[0], additionInfo[1], static_cast<CellType>(additionInfo[2])));
    }
    drawCellsFromQueue(queue.get());
}

void MainWindow::drawCellsFromQueue(const std::vector<PaintCellInfo>& cells)
{
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
    drawCellsFromQueue(mp_currSolution->getQueue().get());
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
            Q_ASSERT_X(m_levelsStorage.getLevelsList().contains(it.key()), "MainWindow::actionChangeLevel", "name didnt Exist");
            m_levelsStorage.setProperties(it.key(), it.value());
        }

        changeNonogram(lvlChangeDlg->getChosenLevelName());
    }
}

void MainWindow::actionSaveLevels()
{
    m_levelsStorage.saveSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    actionSaveLevels();
    event->accept();
}

void MainWindow::actionCondionsLevelCreate()
{
    QStringList levelsName = m_levelsStorage.getLevelsList();
    std::unique_ptr<ConditionLevelCreate> lvlCreateDlg = std::make_unique<ConditionLevelCreate>(levelsName);
    if (lvlCreateDlg->exec())
    {
        std::shared_ptr<LevelData> newLevel = std::make_shared<LevelData>();
        newLevel->isLoadedDataInformation = true;
        newLevel->data = lvlCreateDlg->getData();
        newLevel->properties = lvlCreateDlg->getProperties();

        m_levelsStorage.addLevel(lvlCreateDlg->getLevelName(), newLevel);
    }
}
