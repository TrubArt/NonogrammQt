#ifndef CONDITIONLEVELCREATE_H
#define CONDITIONLEVELCREATE_H

#include <QDialog>
#include <QLabel>
#include <QVector>

#include "scrollareaconditioncontent.h"

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
    void addClicked();
    void deleteClicked();

private:
    ScrollAreaConditionContent* scrollAreaInit(QScrollArea* scrollArea);
    void connectInitialization();

    bool firstPageDataCheck();
    bool secAndThirdPageDataCheck();
    bool fourthPageDataCheck();

    void remakeScrollAreaSource();

    Ui::ConditionLevelCreate* ui;
    QStringList m_levelsName;
    QVector<QLabel*> m_sections;

    ScrollAreaConditionContent* m_linesContents;
    ScrollAreaConditionContent* m_columnsContents;
    ScrollAreaConditionContent* m_additionContents;

    const QString m_errorBack = "QLabel{background-color: rgba(255, 85, 127, 255);}";
    const QString m_normalBack = "QLabel{background-color: rgba(0, 0, 0, 0);}";
};

#endif // CONDITIONLEVELCREATE_H
