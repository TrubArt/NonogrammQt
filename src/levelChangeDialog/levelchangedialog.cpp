#include "levelchangedialog.h"
#include "ui_levelchangedialog.h"
#include "../levelsManager/levelsDirectory.h"

#include <QPainter>

LevelChangeDialog::LevelChangeDialog(const QString& lastLvlName, LevelsStorage::dataType& lvlsData, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LevelChangeDialog)
    , m_levelsData(lvlsData)
{
    ui->setupUi(this);
    setWindowTitle(tr("Level selection"));

    createTableUI();
    connectInitialization();
    setPreviousLevelName(lastLvlName);
}

LevelChangeDialog::~LevelChangeDialog()
{
    delete ui;
}

void LevelChangeDialog::createTableUI()
{
    ui->levelsTable->setColumnCount(2);
    ui->levelsTable->setShowGrid(true);
    ui->levelsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->levelsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList headers = { tr("Level"), tr("Size") };
    ui->levelsTable->setHorizontalHeaderLabels(headers);

    setLevels();

    ui->levelsTable->resizeColumnToContents(static_cast<int>(ColumnsName::size));
    ui->levelsTable->horizontalHeader()->setSectionResizeMode(static_cast<int>(ColumnsName::name), QHeaderView::Stretch);
}

void LevelChangeDialog::paintColorSetting(QLabel* label, const QColor& color)
{
    QPixmap pixmap(16, 16);
    QPainter painter;
    painter.begin(&pixmap);
    painter.drawRect(0, 0, 16 ,16);
    painter.fillRect(0, 0, 16, 16, QBrush(color));
    painter.end();

    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void LevelChangeDialog::updateSettingsViewUI()
{
    std::shared_ptr<LevelData> lvlData = m_levelsData[m_chosenLvlName];
    paintColorSetting(ui->blackColorLabel, lvlData->colors.getBlack());
    paintColorSetting(ui->whiteColorLabel, lvlData->colors.getWhite());
    paintColorSetting(ui->undefinedColorLabel, lvlData->colors.getUndefine());
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

void LevelChangeDialog::setLevels()
{
    auto sizeLikeString = [](int rowCount, int columnCount) -> QString
    {
        return QString::number(rowCount) + "x" + QString::number(columnCount);
    };

    int rowIndex = 0;
    for (auto it = m_levelsData.begin(); it != m_levelsData.end(); ++it)
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
    QString newLevelName = selection[static_cast<int>(ColumnsName::name)]->text();

    m_chosenLvlName = newLevelName;
    updateSettingsViewUI();
}
