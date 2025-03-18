#ifndef TABLE_H
#define TABLE_H

#include <qgraphicsscene.h>

#include "colorstore.h"

class Table
{
public:
    Table();
    ~Table() = default;

    const QGraphicsScene* get() const;
    QGraphicsScene* get();

    void repaintTable(int heightCountCell, int widthCountCell);
    int getHeight() const;
    int getWidth() const;

    void repaintCell(int heightIndex, int widthIndex, CellType col);
    void resetTableCells();

    void createTable();
    void removeTable();

private:
    void setCellSize();

    QPoint findTopLeftPointCell(int heightIndex, int widthIndex) const;
    QPoint findCenterCell(int heightIndex, int widthIndex) const;

    void addCell(int heightIndex, int widthIndex, const QPen& pen, const QColor& col);
    void removeCell(int heightIndex, int widthIndex);

    QGraphicsScene m_scene;

    QSizeF m_rectSize;
    int m_height;
    int m_width;

    ColorStore m_colors;
};

#endif // TABLE_H
