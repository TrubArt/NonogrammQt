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
    explicit ConditionLevelCreate(const QStringList& levelsName, QWidget* parent = nullptr);
    ~ConditionLevelCreate() override;
    bool checkDataValidation(int pageIndex);
    void setSectionsFont(int newPageIndex, ButtonClicked button);

public slots:
    void backClicked();
    void nextClicked();

private:
    void connectInitialization();

    bool firstPageDataCheck();
    bool secAndThirdPageDataCheck();
    bool fourthPageDataCheck();

    Ui::ConditionLevelCreate* ui;
    QStringList m_levelsName;
    QVector<QLabel*> m_sections;

    const QString m_errorBack = "QLabel{background-color: rgba(255, 85, 127, 255);}";
    const QString m_normalBack = "QLabel{background-color: rgba(0, 0, 0, 0);}";
};

#endif // CONDITIONLEVELCREATE_H
