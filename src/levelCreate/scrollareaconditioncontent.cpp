#include "scrollareaconditioncontent.h"
#include <QScrollBar>

ScrollAreaConditionContent::ScrollAreaConditionContent(QWidget* parent)
    : QWidget(parent)
    , m_viewSize(0)
{}

void ScrollAreaConditionContent::setScrollArea(QScrollArea* sa)
{
    m_parentScrollArea = sa;
}

int ScrollAreaConditionContent::getViewSize() const
{
    return m_viewSize;
}

void ScrollAreaConditionContent::updateContent(int newSize)
{
    const QSize shiftFromTopLeft(10, 10);
    const int labelWidth = 30;

    int maxWidth = 0;
    if (m_viewSize == 0)   // first painting
    {
        m_conditions.reserve(newSize);

        QRect geometry(shiftFromTopLeft.width(), shiftFromTopLeft.height(), 0, 0);
        for (int i = 0; i < newSize; ++i)
        {
            ConditionElement* condition = new ConditionElement(i + 1, this);
            m_conditions.push_back(condition);
            condition->setLabelWidth(labelWidth);

            int condWidth = condition->width();
            maxWidth = std::max(maxWidth, condWidth);

            geometry.setTop(geometry.bottom() + 1);
            geometry.setBottom(geometry.top() + condition->height());
            geometry.setRight(geometry.left() + condWidth);

            condition->setGeometry(geometry);
        }

        int rightShift = m_parentScrollArea->verticalScrollBar()->height() + 10; // 10 - margins
        setFixedSize(maxWidth + rightShift, geometry.bottom());
        m_viewSize = newSize;
    }
    else if (newSize < m_viewSize)
    {
        QSize sizeContetns = size();
        int finalBottomValue = sizeContetns.height();
        for (int i = newSize; i < m_viewSize; ++i)
        {
            finalBottomValue -= m_conditions[i]->height();
            m_conditions[i]->setVisible(false);
        }
        setFixedSize(sizeContetns.width(), finalBottomValue);
        m_viewSize = newSize;
    }
    else if (newSize > m_viewSize)
    {
        m_viewSize = newSize;
    }
    else
    {
        Q_ASSERT_X(false, "ScrollAreaConditionContent::updateContent", "undefined action");
    }
}
