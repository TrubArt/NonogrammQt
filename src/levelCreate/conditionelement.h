#ifndef CONDITIONELEMENT_H
#define CONDITIONELEMENT_H

#include <QLineEdit>

namespace Ui
{
class ConditionElement;
}

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    using QLineEdit::QLineEdit;

signals:
    void getFocus();
    void lostFocus();

protected:
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
};



class ConditionElement : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionElement(int number, QWidget* parent = nullptr);
    ~ConditionElement() override;

    void setLabelWidth(int width);
    void setText(const QString& value);
    void setStyleSheetLineEdit(const QString& styleSheet);
    int getNumber() const;
    QString getData() const;

protected:
    void focusInEvent(QFocusEvent*) override;

signals:
    void getFocus(int value);
    void lostFocus();

private slots:
    void getFocusHandler();

private:
    Ui::ConditionElement* ui;
};

#endif // CONDITIONELEMENT_H
