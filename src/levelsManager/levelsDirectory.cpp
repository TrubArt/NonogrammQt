#include "levelsDirectory.h"

LevelsDirectory::LevelsDirectory()
    : m_directory(QDir::currentPath() + QDir::separator() + "levels")
{}

QString LevelsDirectory::path() const
{
    return m_directory.path();
}

QStringList LevelsDirectory::levelsList() const
{
    return m_directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
}

QString LevelsDirectory::getAbsPath(const QString& levelName) const
{
    return path() + "/" + levelName;
}
