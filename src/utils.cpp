#include "utils.h"
#include <QMessageBox>

namespace utils
{

void sendMessage(const QString& winTitle, const QString& text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(winTitle);
    msgBox.setText(text);
    msgBox.exec();
}

}
