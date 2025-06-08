#include "utils.h"

#include <QMessageBox>
#include <QDir>

namespace utils
{

void sendMessage(const QString& winTitle, const QString& text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(winTitle);
    msgBox.setText(text);
    msgBox.exec();
}

bool deleteFullDirectory(const QString& path)
{
    QDir dir(path);
    const QFileInfoList fileList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

    bool result = true;
    QFile file;
    for (auto it = fileList.constBegin(), end = fileList.constEnd(); result && it != end; ++it)
    {
        const QString fileName = it->absoluteFilePath();
        file.setFileName(fileName);

        result = it->isDir() ? deleteFullDirectory(fileName) : file.remove();

        if (!result)
        {
            qDebug() << file.errorString();
        }
    }

    return result && dir.rmdir(path);
}

}
