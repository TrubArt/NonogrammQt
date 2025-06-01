#include "tablelevels.h"
#include "ui_tablelevels.h"
#include "../levelCreate/datalevelchange.h"
#include <QMessageBox>

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

void TableLevels::deleteLevelView(int index)
{
    ui->levelsTable->removeRow(index);
}

void TableLevels::connectInitialization()
{
    connect(ui->levelsTable, &QTableWidget::itemSelectionChanged, this, &TableLevels::selectionChanged);
    connect(ui->levelsTable, &QTableWidget::itemDoubleClicked, this, &TableLevels::newLevelChoice);
    connect(ui->pbAddLevel, &QPushButton::clicked, this, &TableLevels::condionsLevelCreate);
    connect(ui->pbEditLevel, &QPushButton::clicked, this, &TableLevels::editLevel);
    connect(ui->pbDeleteLevel, &QPushButton::clicked, this, &TableLevels::deleteLevel);
}

QString TableLevels::curLevelName() const
{
    QList<QTableWidgetItem*> selection = ui->levelsTable->selectedItems();
    QString levelName = selection[static_cast<int>(ColumnsName::name)]->text();
    return levelName;
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

void TableLevels::deleteLevel()
{
    QString levelName = curLevelName();

    QMessageBox msg;
    msg.setWindowTitle(tr("Delete Level"));
    msg.setText(tr("Do you really want to remove this level - ") + levelName + "?");

    msg.setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    int ret = msg.exec();
    if (ret == QMessageBox::StandardButton::No)
    {
        return;
    }

    m_levels.deleteLevel(levelName);

    int removeRowIndex = ui->levelsTable->currentRow();
    deleteLevelView(removeRowIndex);

    emit levelDelete(levelName);
}

void TableLevels::selectionChanged()
{
    bool enabled = false;
    if (ui->levelsTable->selectedItems().size() != 0)
    {
        enabled = true;
    }

    ui->pbDeleteLevel->setEnabled(enabled);
    ui->pbEditLevel->setEnabled(enabled);
}

void TableLevels::editLevel()
{
    QString oldLevelName = curLevelName();
    m_levels.loadDataInformationToApp(oldLevelName);
    const std::shared_ptr<LevelData> curLevelData = m_levels.getLevelData(oldLevelName);
    Q_ASSERT_X(curLevelData, "TableLevels::changeLevel", "level not exist!");

    std::unique_ptr<DataLevelChange> levelChangeDlg = std::make_unique<DataLevelChange>(oldLevelName, curLevelData, m_levels.getLevelsList(), this);
    if (levelChangeDlg->exec())
    {
        std::shared_ptr<LevelData> newLevel = std::make_shared<LevelData>();
        newLevel->isLoadedDataInformation = true;
        newLevel->data = levelChangeDlg->getData();
        newLevel->properties = levelChangeDlg->getProperties();
        QString newLevelName = levelChangeDlg->getLevelName();

        m_levels.changeLevelData(oldLevelName, newLevelName, newLevel);

        int currentRowIndex = ui->levelsTable->currentRow();
        deleteLevelView(currentRowIndex);
        addLevelView(currentRowIndex, newLevelName, newLevel->properties.rowCount, newLevel->properties.columnCount);
    }
}
