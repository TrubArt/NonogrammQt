#include "table.h"

Table::Table()
    : mp_scene(new QGraphicsScene())
    , m_height(0)
    , m_width(0)
{
    setCellSize();
}

Table::~Table()
{
    delete mp_scene;
}

QGraphicsScene* Table::get()
{
    return mp_scene;
}

void Table::setTableSize(int heightCountCell, int widthCountCell)
{
    removeTable();

    m_height = heightCountCell;
    m_width = widthCountCell;

    setCellSize();

    createTable();
}

int Table::getHeight() const
{
    return m_height;
}

int Table::getWidth() const
{
    return m_width;
}


void Table::setCellSize()
{
    int sizeValue = 20;
    m_rectSize.setWidth(sizeValue);
    m_rectSize.setHeight(sizeValue);
}

QPoint Table::findTopLeftPointCell(int heightIndex, int widthIndex) const
{
    QPoint answer(widthIndex * m_rectSize.width(), heightIndex * m_rectSize.height());
    return answer;
}

QPoint Table::findCenterCell(int heightIndex, int widthIndex) const
{
    QPoint cellLeftTop = findTopLeftPointCell(heightIndex, widthIndex);
    QPoint centerElem(cellLeftTop.x() + m_rectSize.width() / 2, cellLeftTop.y() + m_rectSize.height() / 2);
    return centerElem;
}

void Table::removeCell(int heightIndex, int widthIndex)
{
    QPoint centerElem = findCenterCell(heightIndex, widthIndex);
    QGraphicsItem * elem = mp_scene->itemAt(centerElem, QTransform());
    mp_scene->removeItem(elem);
}

void Table::addCell(int heightIndex, int widthIndex, const QPen& pen, const QColor& col)
{
    QPoint topleft = findTopLeftPointCell(heightIndex, widthIndex);
    QRectF rect(topleft, m_rectSize);
    mp_scene->addRect(rect, pen, QBrush(col));
}

void Table::repaintCell(int heightIndex, int widthIndex, CellType col)
{
    removeCell(heightIndex, widthIndex);
    QColor color = colors.convertColorFromCore(col);
    addCell(heightIndex, widthIndex, QPen(Qt::black), color);
}

void Table::createTable()
{
    QPen pen(Qt::black);
    QColor color(colors.getUndefine());

    for (int hIndex = 0; hIndex < m_height; ++hIndex)
    {
        for (int wIndex = 0; wIndex < m_width; ++wIndex)
        {
            addCell(hIndex, wIndex, pen, color);
        }
    }
}

void Table::removeTable()
{
    for (int hIndex = 0; hIndex < m_height; ++hIndex)
    {
        for (int wIndex = 0; wIndex < m_width; ++wIndex)
        {
            removeCell(hIndex, wIndex);
        }
    }
}
