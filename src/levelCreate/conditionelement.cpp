#include "conditionelement.h"
#include "ui_conditionelement.h"


//******************************************//
//              CustomLineEdit              //
//******************************************//


void CustomLineEdit::focusInEvent(QFocusEvent* event)
{
    QWidget::focusInEvent(event);
    emit getFocus();
}

void CustomLineEdit::focusOutEvent(QFocusEvent* event)
{
    QWidget::focusOutEvent(event);
    emit lostFocus();
}


//******************************************//
//              ConditionElement            //
//******************************************//


ConditionElement::ConditionElement(int number, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ConditionElement)
{
    ui->setupUi(this);
    ui->labelNumber->setText(QString::number(number) + ": ");

    connect(ui->lineEditData, &CustomLineEdit::getFocus, this, &ConditionElement::getFocusHandler);
    connect(ui->lineEditData, &CustomLineEdit::lostFocus, this, &ConditionElement::lostFocus);
}

ConditionElement::~ConditionElement()
{
    delete ui;
}

void ConditionElement::setLabelWidth(int width)
{
    ui->labelNumber->setFixedWidth(width);
}

void ConditionElement::setText(const QString& value)
{
    ui->lineEditData->setText(value);
}

void ConditionElement::setStyleSheetLineEdit(const QString& styleSheet)
{
    ui->lineEditData->setStyleSheet(styleSheet);
}

int ConditionElement::getNumber() const
{
    QString text = ui->labelNumber->text().chopped(2);
    return text.toInt();
}

QString ConditionElement::getData() const
{
    return ui->lineEditData->text();
}

void ConditionElement::getFocusHandler()
{
    emit getFocus(getNumber());
}
