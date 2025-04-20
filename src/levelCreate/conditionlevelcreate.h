#ifndef CONDITIONLEVELCREATE_H
#define CONDITIONLEVELCREATE_H

#include <QDialog>
#include <QLabel>
#include <QVector>

namespace Ui
{
class ConditionLevelCreate;
}

class ConditionLevelCreate : public QDialog
{
    Q_OBJECT
private:
    enum class ButtonClicked { back, next };

public:
    explicit ConditionLevelCreate(QWidget* parent = nullptr);
    ~ConditionLevelCreate() override;
    void setSectionsFont(int newPageIndex, ButtonClicked button);

public slots:
    void backClicked();
    void nextClicked();

private:
    void connectInitialization();

    Ui::ConditionLevelCreate* ui;
    QVector<QLabel*> m_sections;
};

#endif // CONDITIONLEVELCREATE_H
