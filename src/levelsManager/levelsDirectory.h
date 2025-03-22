#ifndef LEVELSDIRECTORY_H
#define LEVELSDIRECTORY_H

#include <QtCore/qdir.h>

class LevelsDirectory
{
public:
    LevelsDirectory();
    QString path() const;
    QStringList levelsList() const;

private:
    QDir m_directory;
};

#endif // LEVELSDIRECTORY_H
