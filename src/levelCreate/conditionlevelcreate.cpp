#include "conditionlevelcreate.h"
#include "ui_conditionlevelcreate.h"

ConditionLevelCreate::ConditionLevelCreate(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ConditionLevelCreate)
{
    ui->setupUi(this);
}

ConditionLevelCreate::~ConditionLevelCreate()
{
    delete ui;
}
