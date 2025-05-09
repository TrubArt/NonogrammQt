#include "tablelevels.h"
#include "ui_tablelevels.h"
#include "../levelCreate/conditionlevelcreate.h"

TableLevels::TableLevels(LevelsStorage& levelsStorage, QWidget* parent)
    : QWidget(parent)
    , m_levels(levelsStorage)
    , ui(new Ui::TableLevels)
{
    ui->setupUi(this);

    ui->levelsTable->setColumnCount(2);
    ui->levelsTable->setShowGrid(true);
    ui->levelsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->levelsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->levelsTable->setEditTriggers(QTableWidget::EditTrigger::NoEditTriggers);

    QStringList headers = { tr("Level"), tr("Size") };
    ui->levelsTable->setHorizontalHeaderLabels(headers);

    int rowIndex = 0;
    LevelsStorage::dataType levelsData = m_levels.getData();
    for (auto it = levelsData.begin(); it != levelsData.end(); ++it)
    {
        addLevelView(rowIndex, it.key(), it.value()->properties.rowCount, it.value()->properties.columnCount);
        ++rowIndex;
    }

    ui->levelsTable->horizontalHeader()->setSectionResizeMode(static_cast<int>(ColumnsName::name), QHeaderView::Stretch);

    connectInitialization();
}

TableLevels::~TableLevels()
{
    delete ui;
}

void TableLevels::addLevelView(int insertIndex, const QString& name, int rowCount, int columnCount)
{
    auto sizeLikeString = [](int rowCount, int columnCount) -> QString
    {
        return QString::number(rowCount) + "x" + QString::number(columnCount);
    };

    ui->levelsTable->insertRow(insertIndex);

    ui->levelsTable->setItem(insertIndex, static_cast<int>(ColumnsName::name), new QTableWidgetItem(name));
    ui->levelsTable->setItem(insertIndex, static_cast<int>(ColumnsName::size), new QTableWidgetItem(sizeLikeString(rowCount, columnCount)));

    ui->levelsTable->resizeColumnToContents(static_cast<int>(ColumnsName::size));
}

void TableLevels::connectInitialization()
{
    connect(ui->levelsTable, &QTableWidget::itemDoubleClicked, this, &TableLevels::newLevelChoice);
    connect(ui->pbAddLevel, &QPushButton::clicked, this, &TableLevels::condionsLevelCreate);
    connect(ui->pbDeleteLevel, &QPushButton::clicked, this, &MainWindow::levelDelete);
}

void TableLevels::condionsLevelCreate()
{
    QStringList levelsName = m_levels.getLevelsList();
    std::unique_ptr<ConditionLevelCreate> lvlCreateDlg = std::make_unique<ConditionLevelCreate>(levelsName);
    if (lvlCreateDlg->exec())
    {
        std::shared_ptr<LevelData> newLevel = std::make_shared<LevelData>();
        newLevel->isLoadedDataInformation = true;
        newLevel->data = lvlCreateDlg->getData();
        newLevel->properties = lvlCreateDlg->getProperties();
        QString newLevelName = lvlCreateDlg->getLevelName();

        m_levels.addLevel(newLevelName, newLevel);
        addLevelView(ui->levelsTable->rowCount(), newLevelName, newLevel->properties.rowCount, newLevel->properties.columnCount);
    }
}
