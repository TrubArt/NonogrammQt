#include "levelsDirectory.h"

LevelsDirectory::LevelsDirectory()
    : m_directory(QDir::currentPath() + "/levels")
{}

QString LevelsDirectory::path() const
{
    return m_directory.path();
}

QStringList LevelsDirectory::levelsList() const
{
    return m_directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
}
