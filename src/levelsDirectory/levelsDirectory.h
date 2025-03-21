#ifndef LEVELSDIRECTORY_H
#define LEVELSDIRECTORY_H

#include <QDir>

class LevelsDirectory
{
public:
    LevelsDirectory();
    QString path() const;

private:
    QDir m_directory;
};

#endif // LEVELSDIRECTORY_H
