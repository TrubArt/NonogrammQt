#ifndef CONDITIONLEVELCREATE_H
#define CONDITIONLEVELCREATE_H

#include <QDialog>

namespace Ui
{
class ConditionLevelCreate;
}

class ConditionLevelCreate : public QDialog
{
    Q_OBJECT

public:
    explicit ConditionLevelCreate(QWidget* parent = nullptr);
    ~ConditionLevelCreate() override;

private:
    Ui::ConditionLevelCreate* ui;
};

#endif // CONDITIONLEVELCREATE_H
