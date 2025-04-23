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

    if (m_viewSize == 0)   // first painting
    {
        m_conditions.reserve(newSize);

        int maxWidth = 0;
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
    }
    else if (newSize > m_viewSize)
    {
        int indexStart = m_viewSize;
        int numOfExistConditions = m_conditions.size();

        QSize sizeContetns = size();
        int finalBottomValue = sizeContetns.height();

        if (m_viewSize <= numOfExistConditions)
        {
            for (; indexStart < numOfExistConditions; ++indexStart)
            {
                finalBottomValue += m_conditions[indexStart]->height();
                m_conditions[indexStart]->setVisible(true);
            }
        }

        int maxWidth = 0;
        QRect geometry(shiftFromTopLeft.width(), finalBottomValue, 0, 0);
        for (; indexStart < newSize; ++indexStart)
        {
            ConditionElement* condition = new ConditionElement(indexStart + 1, this);
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
    }
    else
    {
        Q_ASSERT_X(false, "ScrollAreaConditionContent::updateContent", "undefined action");
    }

    m_viewSize = newSize;
}
