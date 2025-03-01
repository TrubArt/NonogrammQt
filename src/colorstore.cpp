#include "colorstore.h"

ColorStore::ColorStore()
{
    returnToStandart();
}

void ColorStore::returnToStandart()
{
    setUndefine();
    setWhite();
    setBlack();
}

void ColorStore::setUndefine(const QColor& u)
{
    undefined = u;
}

void ColorStore::setWhite(const QColor& w)
{
    white = w;
}

void ColorStore::setBlack(const QColor& b)
{
    black = b;
}

QColor ColorStore::getUndefine() const
{
    return undefined;
}

QColor ColorStore::getWhite() const
{
    return white;
}

QColor ColorStore::getBlack() const
{
    return black;
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
