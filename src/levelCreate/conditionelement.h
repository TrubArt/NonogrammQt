#ifndef CONDITIONELEMENT_H
#define CONDITIONELEMENT_H

#include <QWidget>

namespace Ui
{
class ConditionElement;
}

class ConditionElement : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionElement(int number, QWidget* parent = nullptr);
    ~ConditionElement() override;

    void setLabelWidth(int width);
    int getNumber() const;
    QString getData() const;

private:
    Ui::ConditionElement* ui;
};

#endif // CONDITIONELEMENT_H
