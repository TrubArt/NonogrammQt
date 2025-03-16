#include "levelchangedialog.h"
#include "ui_levelchangedialog.h"

LevelChangeDialog::LevelChangeDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LevelChangeDialog)
{
    ui->setupUi(this);
}

LevelChangeDialog::~LevelChangeDialog()
{
    delete ui;
}
