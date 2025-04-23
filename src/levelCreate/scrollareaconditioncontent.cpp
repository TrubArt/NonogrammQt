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

        QSize sizeContetns = size();
        int condWidth = ConditionElement(0).size().width();
        QRect geometry(shiftFromTopLeft.width(), shiftFromTopLeft.height(), 0, 0);

        for (int i = 0; i < newSize; ++i)
        {
            ConditionElement* condition = new ConditionElement(i + 1, this);
            m_conditions.push_back(condition);
            condition->setLabelWidth(labelWidth);

            geometry.setTop(geometry.bottom());
            int condHeight = condition->height();
            geometry.setBottom(geometry.top() + condHeight);
            geometry.setRight(geometry.left() + condWidth);

            condition->setGeometry(geometry);
        }

        int rightShift = m_parentScrollArea->verticalScrollBar()->height() + 10; // 10 - margins
        setFixedSize(condWidth + rightShift, geometry.bottom());
    }
    else if (newSize < m_viewSize)
    {
        QSize sizeContetns = size();
        int finalBottomValue = sizeContetns.height();
        for (int i = newSize; i < m_viewSize; ++i)
        {
            int height = m_conditions[i]->height() - 1; // -1 needs because QT is good mathematic :)
            finalBottomValue -= height;
            m_conditions[i]->setVisible(false);
        }
        setFixedSize(sizeContetns.width(), finalBottomValue);
    }
    else if (newSize > m_viewSize)
    {
        int indexStart = m_viewSize;
        int numOfExistConditions = m_conditions.size();

        QSize sizeContetns = size();
        int condWidth = ConditionElement(0).size().width();
        int finalBottomValue = sizeContetns.height();

        if (m_viewSize < numOfExistConditions)
        {
            int limit = std::min(newSize, numOfExistConditions);
            for (; indexStart < limit; ++indexStart)
            {
                finalBottomValue += m_conditions[indexStart]->height();
                m_conditions[indexStart]->setVisible(true);
            }
        }

        QRect geometry(shiftFromTopLeft.width(), finalBottomValue, 0, 0);
        for (; indexStart < newSize; ++indexStart)
        {
            ConditionElement* condition = new ConditionElement(indexStart + 1, this);
            m_conditions.push_back(condition);
            condition->setLabelWidth(labelWidth);

            geometry.setTop(geometry.bottom());
            geometry.setBottom(geometry.top() + condition->height());
            geometry.setRight(geometry.left() + condWidth);

            condition->setGeometry(geometry);
        }

        int rightShift = m_parentScrollArea->verticalScrollBar()->height() + 10; // 10 - margins
        setFixedSize(condWidth + rightShift, geometry.bottom());
    }
    else
    {
        Q_ASSERT_X(false, "ScrollAreaConditionContent::updateContent", "undefined action");
    }

    m_viewSize = newSize;
}
