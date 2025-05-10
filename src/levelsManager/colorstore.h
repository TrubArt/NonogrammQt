#ifndef COLORSTORE_H
#define COLORSTORE_H

#include <QColor>

#include "picture/cell.h"

class ColorStore
{
public:
    ColorStore();

    void returnToDefault();

    void setUndefine(const QColor& u = Qt::lightGray);
    void setWhite(const QColor& w = Qt::white);
    void setBlack(const QColor& b = Qt::black);

    QColor getUndefine() const;
    QColor getWhite() const;
    QColor getBlack() const;

    QColor convertColorFromCore(CellType cellColor) const;

private:
    QColor m_undefined;
    QColor m_white;
    QColor m_black;
};

#endif // COLORSTORE_H
