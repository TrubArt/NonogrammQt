#include "levelchangedialog.h"
#include "ui_levelchangedialog.h"
#include "../levelsManager/levelsDirectory.h"

LevelChangeDialog::LevelChangeDialog(const QString& lastLvlName, const LevelsDirectory& lvlDir, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LevelChangeDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Level selection"));

    setLevels(lvlDir);
    connectInitialization();

    QList<QListWidgetItem*> names = ui->levelsList->findItems(lastLvlName, Qt::MatchExactly);
    if (!names.empty())
    {
        ui->levelsList->setCurrentItem(names[0]);
    }
    else
    {
        ui->levelsList->setCurrentRow(0);
    }
}

LevelChangeDialog::~LevelChangeDialog()
{
    delete ui;
}

void LevelChangeDialog::connectInitialization()
{
    connect(ui->levelsList, &QListWidget::itemSelectionChanged, this, LevelChangeDialog::nameChanged);
    connect(ui->levelsList, &QListWidget::itemDoubleClicked, this, LevelChangeDialog::accept);
}

const QString& LevelChangeDialog::getChosenLevelName() const
{
    return m_chosenLvlName;
}

void LevelChangeDialog::setLevels(const LevelsDirectory& lvlDir)
{
    QListWidget* uiLevels = ui->levelsList;
    QStringList levels = lvlDir.levelsList();

    for (const auto& levelName : levels)
    {
        uiLevels->addItem(levelName);
    }
}

void LevelChangeDialog::nameChanged()
{
    QList<QListWidgetItem*> selection = ui->levelsList->selectedItems();
    m_chosenLvlName = selection[0]->text();
}
