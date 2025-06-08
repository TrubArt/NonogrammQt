#include "scrollareaconditioncontent.h"
#include <QScrollBar>
#include <QKeyEvent>

ScrollAreaConditionContent::ScrollAreaConditionContent(QWidget* parent)
    : QWidget(parent)
    , m_parentScrollArea(nullptr)
    , m_viewSize(0)
    , m_curFocusIndex(-1)
{}

void ScrollAreaConditionContent::setScrollArea(QScrollArea* sa)
{
    m_parentScrollArea = sa;
}

int ScrollAreaConditionContent::getViewSize() const
{
    return m_viewSize;
}

int ScrollAreaConditionContent::getRealSize() const
{
    return m_conditions.size();
}

void ScrollAreaConditionContent::updateContent(int newSize)
{
    if (newSize < m_viewSize)
    {
        const QSize sizeContents = size();
        int finalBottomValue = sizeContents.height();
        for (int i = newSize; i < m_viewSize; ++i)
        {
            int height = m_conditions[i]->height() - 1; // -1 needs because QT is good mathematic :)
            finalBottomValue -= height;
            m_conditions[i]->setVisible(false);
        }
        setFixedSize(sizeContents.width(), finalBottomValue);
    }
    else if (newSize > m_viewSize)
    {
        const QSize sizeContents = size();
        const int numOfExistConditions = m_conditions.size();

        int indexStart = m_viewSize;
        int finalBottomValue = sizeContents.height();

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
        if (numOfExistConditions == 0)   // first painting
        {
            geometry = QRect(shiftFromTopLeft.width(), shiftFromTopLeft.height() + 1, 0, 0);
        }
        else
        {
            geometry = QRect(shiftFromTopLeft.width(), finalBottomValue + 1, 0, 0);
        }

        m_conditions.reserve(newSize);
        for (; indexStart < newSize; ++indexStart)
        {
            ConditionElement* condition = new ConditionElement(indexStart + 1, this);
            connect(condition, &ConditionElement::getFocus, this, &ScrollAreaConditionContent::focusInHandler);
            connect(condition, &ConditionElement::lostFocus, this, &ScrollAreaConditionContent::focusOutHandler);

            m_conditions.push_back(condition);
            condition->setLabelWidth(labelWidth);

            geometry.setTop(geometry.bottom());
            geometry.setBottom(geometry.top() + condition->height());
            geometry.setRight(geometry.left() + condWidth);

            condition->setVisible(false);
            condition->setGeometry(geometry);
            condition->setVisible(true);
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

const QVector<ConditionElement*>& ScrollAreaConditionContent::getConditions() const
{
    return m_conditions;
}

QVector<ConditionElement*>& ScrollAreaConditionContent::getConditions()
{
    return m_conditions;
}

void ScrollAreaConditionContent::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Down && m_curFocusIndex != -1)
    {
        int newFocusWidgetIndex = m_curFocusIndex + 1;
        if (newFocusWidgetIndex == m_viewSize)
        {
            newFocusWidgetIndex = 0;
        }

        m_conditions[newFocusWidgetIndex]->setFocus();
        return;
    }

    if (event->key() == Qt::Key_Up && m_curFocusIndex != -1)
    {
        int newFocusWidgetIndex = m_curFocusIndex - 1;
        if (newFocusWidgetIndex == -1)
        {
            newFocusWidgetIndex = m_viewSize - 1;
        }

        m_conditions[newFocusWidgetIndex]->setFocus();
        return;
    }

    QWidget::keyPressEvent(event);
}

void ScrollAreaConditionContent::focusInHandler(int value)
{
    m_curFocusIndex = value - 1;
}

void ScrollAreaConditionContent::focusOutHandler()
{
    m_curFocusIndex = -1;
}
