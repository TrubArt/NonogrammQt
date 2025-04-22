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
    void updateContent(int newSize);

private:
    QScrollArea* m_parentScrollArea;
    QVector<ConditionElement*> m_conditions;
    int m_viewSize;
};

#endif // SCROLLAREACONDITIONCONTENT_H
