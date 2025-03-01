#ifndef TABLE_H
#define TABLE_H

#include <qgraphicsscene.h>

#include "colorstore.h"

class Table
{
public:
    Table();
    ~Table();

    QGraphicsScene* get();
    void setTableSize(int heightCountCell, int widthCountCell);
    int getHeight() const;
    int getWidth() const;

    QPoint findTopLeftPointCell(int heightIndex, int widthIndex) const;
    QPoint findCenterCell(int heightIndex, int widthIndex) const;

    void repaintCell(int heightIndex, int widthIndex, CellType col);

    void createTable();
    void removeTable();

private:
    void setCellSize();

    void addCell(int heightIndex, int widthIndex, const QPen& pen, const QColor& col);
    void removeCell(int heightIndex, int widthIndex);

    QGraphicsScene* mp_scene;

    QSizeF m_rectSize;
    int m_height;
    int m_width;

    ColorStore colors;
};

#endif // TABLE_H
