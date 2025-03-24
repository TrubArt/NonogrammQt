#include <QTextStream>

#include "levelLoader.h"
#include "../../settings/settings.h"
#include "fileParser.h"

bool LevelLoader::Checker::checkDataValidation(Categories category, const QString& specialization, const QStringList& parameters)
{
    auto findBadParameter = [](const QString& specialization, const QString& value)
    {
        qCritical() << QObject::tr("Bad values!")
                    << QObject::tr(" Parameter: ") << specialization
                    << QObject::tr(" Value: ") << value;
    };

    for (const QString& value : parameters)
    {
        if (category == Categories::levelData || category == Categories::size)
        {
            bool goodValue = checkSize(value);
            if (!goodValue)
            {
                findBadParameter(specialization, value);
                return false;
            }
        }
        else if (category == Categories::color)
        {
            //-------------------------
        }
        else
        {
            Q_ASSERT_X(false, "LevelLoader::Checker::checkData" , "Unresolved category");
        }
    }

    return true;
}

bool LevelLoader::Checker::isOneSettingsInLine(const QStringList& parameters)
{
    return parameters.size() == 1 ? true : false;
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
    QStringList values;
    bool findRowCount = false, findColumnCount = false;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        FileParser::getSettingsData(line, parametr, values);


        if (parametr == LevelSettings::rowCount())
        {
            findRowCount = true;
            if (Checker::checkDataValidation(Categories::size, parametr, values))
            {
                sizes.first = values[0].toInt();
            }
        }
        if (parametr == LevelSettings::columnCount())
        {
            findColumnCount = true;
            if (Checker::checkDataValidation(Categories::size, parametr, values))
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
    std::vector<std::array<size_t, 3>> condition;

    QTextStream in(&m_file);
    QStringList values;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.isEmpty())
        {
            continue;
        }

        FileParser::getLevelData(line, values);

        if (Checker::checkDataValidation(Categories::size, QObject::tr("additional level data value"), values))
        {
            if (values.size() != 3)
            {
                QString lineOfValues;
                for (const QString& value : values)
                {
                    lineOfValues.push_back(value + " ");
                }
                qCritical() << QObject::tr("Error in addition color condition. ")
                            << QObject::tr("Must have only 3 arguments in line: ") << lineOfValues;
            }
            else
            {
                std::array<size_t, 3> oneAdditionalCondition =
                {
                    values[0].toInt(),
                    values[1].toInt(),
                    values[2].toInt()
                };
                condition.push_back(oneAdditionalCondition);
            }
        }
    }

    return condition;
}

std::vector<size_t> LevelLoader::getLineSequence(bool isColumn, size_t lineIndex)
{
    std::vector<size_t> condition;

    QTextStream in(&m_file);
    QList<QString> values;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.isEmpty())
        {
            continue;
        }

        FileParser::getLevelData(line, values);

        if (Checker::checkDataValidation(Categories::size, QObject::tr("level data value"), values))
        {
            condition.reserve(values.size());
            for (const QString& value : values)
            {
                condition.push_back(value.toInt());
            }
        }
    }

    if (condition.empty())
    {
        qCritical() << QObject::tr("Not find condition to") << " "
                    << isColumn ? QObject::tr("column") : QObject::tr("line") << " "
                    << QObject::tr("condition number: ") << lineIndex;
    }
    return condition;
}
