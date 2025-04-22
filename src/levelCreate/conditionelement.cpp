#include "conditionelement.h"
#include "ui_conditionelement.h"
#include <QString>

ConditionElement::ConditionElement(int number, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ConditionElement)
{
    ui->setupUi(this);
    ui->labelNumber->setText(QString::number(number) + ": ");
}

ConditionElement::~ConditionElement()
{
    delete ui;
}

void ConditionElement::setLabelWidth(int width)
{
    ui->labelNumber->setFixedWidth(width);
}
int ConditionElement::getNumber() const
{
    return ui->labelNumber->text().toInt();
}

QString ConditionElement::getData() const
{
    return ui->lineEditData->text();
}
