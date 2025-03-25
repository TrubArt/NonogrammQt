#ifndef LEVELSDIRECTORY_H
#define LEVELSDIRECTORY_H

#include <QDir>

class LevelsDirectory
{
public:
    LevelsDirectory();
    QString path() const;
    QStringList levelsList() const;
    QString getAbsPath(const QString& levelName) const;

private:
    QDir m_directory;
};

#endif // LEVELSDIRECTORY_H
