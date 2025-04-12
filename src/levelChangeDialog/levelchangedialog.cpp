#include "levelchangedialog.h"
#include "ui_levelchangedialog.h"
#include "../levelsManager/levelsDirectory.h"

#include <QPainter>
#include <QColorDialog>

LevelChangeDialog::LevelChangeDialog(const QString& lastLvlName, const LevelsStorage::dataType& lvlsData, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LevelChangeDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Level selection"));

    createPropertiesData(lvlsData);
    createTableUI();
    connectInitialization();

    setPreviousLevelName(lastLvlName);
}

LevelChangeDialog::~LevelChangeDialog()
{
    delete ui;
}

void LevelChangeDialog::createPropertiesData(const LevelsStorage::dataType& lvlsData)
{
    for (auto it = lvlsData.begin(); it != lvlsData.end(); ++it)
    {
        m_propertiesData.insert(it.key(), it.value()->properties);
    }
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

void LevelChangeDialog::updateSettingsViewUI()
{
    paintColorSetting(ui->blackColorButton, m_propertiesData[m_chosenLvlName].colors.getBlack());
    paintColorSetting(ui->whiteColorButton, m_propertiesData[m_chosenLvlName].colors.getWhite());
    paintColorSetting(ui->undefinedColorButton, m_propertiesData[m_chosenLvlName].colors.getUndefine());
}

void LevelChangeDialog::connectInitialization()
{
    connect(ui->levelsTable, &QTableWidget::itemSelectionChanged, this, &LevelChangeDialog::nameChanged);
    connect(ui->levelsTable, &QTableWidget::itemDoubleClicked, this, &LevelChangeDialog::accept);

    connect(ui->blackColorButton, &QPushButton::clicked, this, &LevelChangeDialog::changeBlackColor);
    connect(ui->whiteColorButton, &QPushButton::clicked, this, &LevelChangeDialog::changeWhiteColor);
    connect(ui->undefinedColorButton, &QPushButton::clicked, this, &LevelChangeDialog::changeUndefinedColor);
    connect(ui->resetButton, &QPushButton::clicked, this, &LevelChangeDialog::resetColorToDefault);
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

const QMap<QString, PropertiesInformation>& LevelChangeDialog::getProperties() const
{
    return m_propertiesData;
}

void LevelChangeDialog::setLevels()
{
    auto sizeLikeString = [](int rowCount, int columnCount) -> QString
    {
        return QString::number(rowCount) + "x" + QString::number(columnCount);
    };

    int rowIndex = 0;
    for (auto it = m_propertiesData.begin(); it != m_propertiesData.end(); ++it)
    {
        ui->levelsTable->insertRow(rowIndex);

        ui->levelsTable->setItem(rowIndex, static_cast<int>(ColumnsName::name), new QTableWidgetItem(it.key()));
        ui->levelsTable->setItem(rowIndex, static_cast<int>(ColumnsName::size), new QTableWidgetItem(sizeLikeString(it.value().rowCount, it.value().columnCount)));

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

void LevelChangeDialog::paintColorSetting(QPushButton* button, const QColor& color)
{
    int sizeValue = 16;
    QPixmap pixmap(sizeValue, sizeValue);
    QPainter painter;
    painter.begin(&pixmap);
    painter.drawRect(0, 0, sizeValue ,sizeValue);
    painter.fillRect(0, 0, sizeValue, sizeValue, QBrush(color));
    painter.end();

    button->setFixedSize(QSize(sizeValue, sizeValue));
    button->setIcon(QIcon(pixmap));
    //button->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void LevelChangeDialog::changeBlackColor()
{
    QColor newColor = QColorDialog::getColor(m_propertiesData[m_chosenLvlName].colors.getBlack());
    paintColorSetting(ui->blackColorButton, newColor);
    m_propertiesData[m_chosenLvlName].colors.setBlack(newColor);
}

void LevelChangeDialog::changeWhiteColor()
{
    QColor newColor = QColorDialog::getColor(m_propertiesData[m_chosenLvlName].colors.getWhite());
    paintColorSetting(ui->whiteColorButton, newColor);
    m_propertiesData[m_chosenLvlName].colors.setWhite(newColor);
}

void LevelChangeDialog::changeUndefinedColor()
{
    QColor newColor = QColorDialog::getColor(m_propertiesData[m_chosenLvlName].colors.getUndefine());
    paintColorSetting(ui->undefinedColorButton, newColor);
    m_propertiesData[m_chosenLvlName].colors.setUndefine(newColor);
}

void LevelChangeDialog::resetColorToDefault()
{
    m_propertiesData[m_chosenLvlName].colors = ColorStore();
    updateSettingsViewUI();
}
