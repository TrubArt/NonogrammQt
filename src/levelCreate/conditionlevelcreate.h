#ifndef CONDITIONLEVELCREATE_H
#define CONDITIONLEVELCREATE_H

#include <QDialog>
#include <QLabel>

#include "scrollareaconditioncontent.h"
#include "levelsManager/levelData.h"

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

protected:
    bool firstPageDataCheck();
    virtual bool nameCheck();
    bool conditionPageDataCheck(int curPageIndex);
    bool fourthPageDataCheck();

    void remakeScrollAreaSource();
    bool checkDataValidation(int pageIndex);
    void setSectionsFont(int newPageIndex, ButtonClicked button);

    Ui::ConditionLevelCreate* ui;
    QStringList m_levelsName;
    QVector<QLabel*> m_sections;

    ScrollAreaConditionContent* m_linesContents;
    ScrollAreaConditionContent* m_columnsContents;
    ScrollAreaConditionContent* m_additionContents;

    class Styles
    {
    public:
        static QString lineEditEr() { return "QLineEdit " + errorBack; }
        static QString lineEditNorm() { return "QLineEdit " + normalBack; }
        static QString spinBoxEr() { return "QSpinBox " + errorBack; }
        static QString spinBoxNorm() { return "QSpinBox " + normalBack; }

    private:
        static const QString errorBack;
        static const QString normalBack;
    };

    const QString m_errorWindowName = tr("Data error");
    const QString m_nameExistError = tr("Name already exist!");
    const QString m_nameIsEmptyError = tr("Level name is empty!");

private:
    std::vector<DataInformation::conditionLine> getConditions(const QVector<ConditionElement*>& data, int viewSize) const;
    std::vector<DataInformation::additionCondLine> getAdditions(const QVector<ConditionElement*>& data, int viewSize) const;
    ScrollAreaConditionContent* scrollAreaInit(QScrollArea* scrollArea);
    void connectInitialization();
};

#endif // CONDITIONLEVELCREATE_H
