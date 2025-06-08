#ifndef SCROLLAREACONDITIONCONTENT_H
#define SCROLLAREACONDITIONCONTENT_H

#include <QWidget>
#include <QVector>
#include <QScrollArea>
#include "conditionelement.h"

class ScrollAreaConditionContent : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollAreaConditionContent(QWidget* parent = nullptr);
    void setScrollArea(QScrollArea* sa);
    int getViewSize() const;
    int getRealSize() const;
    void updateContent(int newSize);

    const QVector<ConditionElement*>& getConditions() const;
    QVector<ConditionElement*>& getConditions();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void focusInHandler(int value);
    void focusOutHandler();

private:
    QScrollArea* m_parentScrollArea;
    QVector<ConditionElement*> m_conditions;
    int m_viewSize;

    int m_curFocusIndex;
};

#endif // SCROLLAREACONDITIONCONTENT_H
