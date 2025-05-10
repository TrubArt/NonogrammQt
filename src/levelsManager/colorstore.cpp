#include "colorstore.h"

ColorStore::ColorStore()
{
    returnToDefault();
}

void ColorStore::returnToDefault()
{
    setUndefine();
    setWhite();
    setBlack();
}

void ColorStore::setUndefine(const QColor& u)
{
    m_undefined = u;
}

void ColorStore::setWhite(const QColor& w)
{
    m_white = w;
}

void ColorStore::setBlack(const QColor& b)
{
    m_black = b;
}

QColor ColorStore::getUndefine() const
{
    return m_undefined;
}

QColor ColorStore::getWhite() const
{
    return m_white;
}

QColor ColorStore::getBlack() const
{
    return m_black;
}

QColor ColorStore::convertColorFromCore(CellType cellColor) const
{
    if (cellColor == CellType::undefined)
    {
        return getUndefine();
    }
    if (cellColor == CellType::white)
    {
        return getWhite();
    }
    if (cellColor == CellType::black)
    {
        return getBlack();
    }

    return Qt::magenta;
}
