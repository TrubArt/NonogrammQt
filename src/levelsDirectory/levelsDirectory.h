#ifndef LEVELSDIRECTORY_H
#define LEVELSDIRECTORY_H

#include <QString>

class LevelsDirectory
{
public:
    LevelsDirectory() = default;
    explicit LevelsDirectory(const QString& path);

    void setPath(const QString& path);
    const QString& getPath() const;

private:
    QString m_dir;
};

#endif // LEVELSDIRECTORY_H
