#ifndef CONDITIONLEVELCREATE_H
#define CONDITIONLEVELCREATE_H

#include <QDialog>
#include <QLabel>
#include <QVector>

#include "scrollareaconditioncontent.h"
#include "../levelsManager/levelData.h"

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

    QString getLevelName() const;
    DataInformation getData() const;
    PropertiesInformation getProperties() const;

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
    bool checkDataValidation(int pageIndex);
    void setSectionsFont(int newPageIndex, ButtonClicked button);

    std::vector<std::vector<size_t>> getConditions(const QVector<ConditionElement*>& data) const;
    std::vector<std::array<size_t, 3>> getAdditions(const QVector<ConditionElement*>& data) const;

    Ui::ConditionLevelCreate* ui;
    QStringList m_levelsName;
    QVector<QLabel*> m_sections;

    ScrollAreaConditionContent* m_linesContents;
    ScrollAreaConditionContent* m_columnsContents;
    ScrollAreaConditionContent* m_additionContents;

    const QString m_errorBack = "QLabel{background-color: rgba(255, 85, 127, 255);}";
    const QString m_normalBack = "QLabel{background-color: rgba(0, 0, 0, 0);}";
    const QString m_windowName = tr("Data error");
};

#endif // CONDITIONLEVELCREATE_H
