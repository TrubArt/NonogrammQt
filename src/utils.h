#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace utils
{

void sendMessage(const QString& winTitle, const QString& text);
bool deleteFullDirectory(const QString& path);

}

#endif // UTILS_H
