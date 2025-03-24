#include "levelLoader.h"
#include "../settings/settings.h"
#include <QTextStream>

void LevelLoader::Parser::getDataFromStr(const QString& line, QString& category, QList<QString>& parameters)
{
    QStringList listBySplit = line.split(":");
    category = listBySplit[0];

    QStringList listParametres = listBySplit[1].split(" ");
    parameters.reserve(listParametres.size());
    for (const QString& parametr : listParametres)
    {
        if (!parametr.isEmpty())
        {
            parameters.push_back(parametr);
        }
    }
}

bool LevelLoader::Checker::checkData(Categories category, const QString& specialization, const QList<QString>& parameters)
{
    auto findBadParametr = [](const QString& specialization, const QString& value)
    {
        qCritical() << QObject::tr("Bad values!")
                    << QObject::tr(" Parameter: ") << specialization
                    << QObject::tr(" Value: ") << value;
    };

    for (const QString& value : parameters)
    {
        if (category == Categories::size)
        {
            bool goodValue = checkSize(value);
            if (!goodValue)
            {
                findBadParametr(specialization, value);
                return false;
            }
        }
        else if (category == Categories::color)
        {
            //-------------------------
        }
        else
        {
            Q_ASSERT_X(false, QObject::tr("LevelLoader::Checker::checkData") ,QObject::tr("Unresolved category"));
        }
    }

    return true;
}

bool LevelLoader::Checker::checkSize(const QString& value)
{
    bool checkToConversion = true;
    value.toInt(checkToConversion);
    if (!checkToConversion || value <= 0)
    {
        return false;
    }
}

void LevelLoader::setFile(const std::string& fileName)
{
    m_file.close();

    m_file.setFileName(fileName);
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical << QObject::tr("File ") << fileName << QObject::tr(" dont open!");
    }
}

std::string LevelLoader::getFileName() const
{
    return m_file.fileName().toStdString();
}

std::pair<size_t, size_t> LevelLoader::getNonogramSize()
{
    std::pair<size_t, size_t> sizes;

    QTextStream in(&m_file);
    QString parametr;
    QList<QString> values;
    bool findRowCount = false, findColumnCount = false;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        Parser::getDataFromStr(line, parametr, values);


        if (parametr == LevelSettings::rowCount())
        {
            findRowCount = true;
            if (Checker::checkData(Categories::size, parametr, values))
            {
                sizes.first = values[0].toInt();
            }
        }
        if (parametr == LevelSettings::columnCount())
        {
            findColumnCount = true;
            if (Checker::checkData(Categories::size, parametr, values))
            {
                sizes.second = values[0].toInt();
            }
        }


        if (findRowCount && findColumnCount)
        {
            break;
        }
    }

    QString errorMessage = QObject::tr("Dont find parameter: ");
    if (!findRowCount)
    {
        qCritical() << errorMessage << LevelSettings::rowCount();
    }
    if (!findColumnCount)
    {
        qCritical() << errorMessage << LevelSettings::columnCount();
    }

    return sizes;
}

std::vector<std::array<size_t, 3>> LevelLoader::getAdditionalCondition()
{
    return {};
}

std::vector<size_t> LevelLoader::getLineSequence(bool isColumn, size_t lineIndex)
{
    return {};
}
