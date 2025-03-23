#include "levelLoader.h"
#include "../settings/settings.h"
#include <QTextStream>

void LevelLoader::Parser::getDataFromStr(const QString& line, QString& category, QList<int>& parameters)
{

}

bool LevelLoader::Checker::getDataFromStr(const QString& category, const QList<int>& parameters)
{
    int parametr;
    if (/*...*/)
    {
        qCritical() << "bad values! "
                    << "category: " << category
                    << "parametr: " << parametr;
        return false;
    }

    return true;
}

void LevelLoader::setFile(const std::string& fileName)
{
    m_file.close();

    m_file.setFileName(fileName);
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical << "file " << fileName << " dont open!";
    }
}

std::string LevelLoader::getFileName() const
{
    return m_file.fileName().toStdString();
}

std::pair<size_t, size_t> LevelLoader::getNonogramSize()
{
    std::pair<int, int> sizes;

    QTextStream in(&m_file);
    QString category;
    QList<int> parameters;
    bool findRowCount = false, findColumnCount = false;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        Parser::getDataFromStr(line, category, parameters);


        if (category == LevelSettings::rowCount())
        {
            findRowCount = true;
            if (Checker::getDataFromStr(LevelSettings::rowCount(), parameters))
            {
                sizes.first = parameters[0];
            }
        }
        if (category == LevelSettings::columnCount())
        {
            findColumnCount = true;
            if (Checker::getDataFromStr(LevelSettings::columnCount(), parameters))
            {
                sizes.second = parameters[0];
            }
        }


        if (findRowCount && findColumnCount)
        {
            break;
        }
    }

    if (!findRowCount)
    {
        qCritical() << "dont find category " << LevelSettings::rowCount();
    }
    if (!findColumnCount)
    {
        qCritical() << "dont find category " << LevelSettings::columnCount();
    }

    return sizes;
}

std::vector<std::array<size_t, 3>> LevelLoader::getAdditionalCondition()
{
    return {};
}
std::vector<size_t> LevelLoader::getLineSequence(bool isColumn, size_t lineIndex) { return {}; }
