#include "levelchangedialog.h"
#include "ui_levelchangedialog.h"

LevelChangeDialog::LevelChangeDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LevelChangeDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Level selection"));

    setLevels();
    connectInitialization();

    ui->levelsList->setCurrentRow(0);
}

LevelChangeDialog::~LevelChangeDialog()
{
    delete ui;
}

void LevelChangeDialog::connectInitialization()
{
    connect(ui->levelsList, &QListWidget::itemSelectionChanged, this, LevelChangeDialog::nameChanged);
}

const QString& LevelChangeDialog::getChosenLevelName() const
{
    return m_chosenLvlName;
}

void LevelChangeDialog::setLevels()
{
    QListWidget* levels = ui->levelsList;

    // изменить подгрузку с помощью класса анализирующего директорию
    // пока подгружаем фиксированные папки

    levels->addItem("1");
    levels->addItem("2");
    levels->addItem("3");
}

void LevelChangeDialog::nameChanged()
{
    QList<QListWidgetItem*> selection = ui->levelsList->selectedItems();
    m_chosenLvlName = selection[0]->text();
}
