#include "levelsDirectory.h"

LevelsDirectory::LevelsDirectory(const QString& path)
    : m_dir(path)
{}

void LevelsDirectory::setPath(const QString& path)
{
    m_dir = path;
}

const QString& LevelsDirectory::getPath() const
{
    return m_dir;
}
