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
    if (newSize < m_viewSize)
    {
        const QSize sizeContetns = size();
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
        const QSize sizeContetns = size();
        const int numOfExistConditions = m_conditions.size();

        int indexStart = m_viewSize;
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

        const QSize shiftFromTopLeft(10, 10);
        const int labelWidth = 30;
        const int condWidth = ConditionElement(0).size().width();

        QRect geometry;
        if (m_viewSize == 0)   // first painting
        {
            geometry = QRect(shiftFromTopLeft.width(), shiftFromTopLeft.height(), 0, 0);
        }
        else
        {
            geometry = QRect(shiftFromTopLeft.width(), finalBottomValue, 0, 0);
        }

        m_conditions.reserve(newSize);
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

        const int rightShift = m_parentScrollArea->verticalScrollBar()->height() + 10; // 10 - margins
        setFixedSize(condWidth + rightShift, geometry.bottom());
    }
    else
    {
        Q_ASSERT_X(false, "ScrollAreaConditionContent::updateContent", "m_viewSize == newSize ?");
    }

    m_viewSize = newSize;
}
