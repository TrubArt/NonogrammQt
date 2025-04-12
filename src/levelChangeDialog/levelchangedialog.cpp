#include "levelchangedialog.h"
#include "ui_levelchangedialog.h"
#include "../levelsManager/levelsDirectory.h"

LevelChangeDialog::LevelChangeDialog(const QString& lastLvlName, const LevelsStorage::dataType& lvlsData, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LevelChangeDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Level selection"));

    createTableUI(lvlsData);
    connectInitialization();
    setPreviousLevelName(lastLvlName);
}

LevelChangeDialog::~LevelChangeDialog()
{
    delete ui;
}

void LevelChangeDialog::createTableUI(const LevelsStorage::dataType& lvlsData)
{
    ui->levelsTable->setColumnCount(2);
    ui->levelsTable->setShowGrid(true);
    ui->levelsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->levelsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList headers = { "Level", "Size" };
    ui->levelsTable->setHorizontalHeaderLabels(headers);

    setLevels(lvlsData);

    ui->levelsTable->resizeColumnToContents(static_cast<int>(ColumnsName::size));
    ui->levelsTable->horizontalHeader()->setSectionResizeMode(static_cast<int>(ColumnsName::name), QHeaderView::Stretch);
}

void LevelChangeDialog::connectInitialization()
{
    connect(ui->levelsTable, &QTableWidget::itemSelectionChanged, this, LevelChangeDialog::nameChanged);
    connect(ui->levelsTable, &QTableWidget::itemDoubleClicked, this, LevelChangeDialog::accept);
}

void LevelChangeDialog::setPreviousLevelName(const QString& prevName)
{
    QList<QTableWidgetItem*> names = ui->levelsTable->findItems(prevName, Qt::MatchExactly);
    if (!names.empty())
    {
        ui->levelsTable->setCurrentItem(names[0]);
    }
    else
    {
        ui->levelsTable->setCurrentCell(0, static_cast<int>(ColumnsName::name));
    }
}

const QString& LevelChangeDialog::getChosenLevelName() const
{
    return m_chosenLvlName;
}

void LevelChangeDialog::setLevels(const LevelsStorage::dataType& lvlsData)
{
    auto sizeLikeString = [](int rowCount, int columnCount) -> QString
    {
        return QString::number(rowCount) + "x" + QString::number(columnCount);
    };

    int rowIndex = 0;
    for (auto it = lvlsData.begin(); it != lvlsData.end(); ++it)
    {
        ui->levelsTable->insertRow(rowIndex);

        ui->levelsTable->setItem(rowIndex, static_cast<int>(ColumnsName::name),  new QTableWidgetItem(it.value()->name));
        ui->levelsTable->setItem(rowIndex, static_cast<int>(ColumnsName::size),  new QTableWidgetItem(sizeLikeString(it.value()->rowCount, it.value()->columnCount)));

        ++rowIndex;
    }
}

void LevelChangeDialog::nameChanged()
{
    QList<QTableWidgetItem*> selection = ui->levelsTable->selectedItems();
    m_chosenLvlName = selection[static_cast<int>(ColumnsName::name)]->text();
}
