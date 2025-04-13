#include "levelLoader.h"

#include <memory>
#include <QDebug>

#include "settings.h"
#include "fileParser.h"
#include "checker.h"

void LevelLoader::setFile(const std::string& fileName)
{
    m_file.close();

    m_file.setFileName(QString::fromStdString(fileName));
    if (!m_file.open(QIODevice::ReadOnly))
    {
        qCritical() << "File " << fileName << " not open!";
    }
}

std::string LevelLoader::getFileName() const
{
    return m_file.fileName().toStdString();
}

std::pair<size_t, size_t> LevelLoader::getNonogramSize()
{
    std::pair<size_t, size_t> sizes;

    bool findRowCount = false, findColumnCount = false;
    while (!m_file.atEnd())
    {
        QString parametr;
        QStringList values;

        QString line = m_file.readLine();
        FileParser::getSettingsData(line, parametr, values);

        if (!Checker::is1SettingsInLine(values))
        {
            qCritical() << "Not 1 settings in line: " << line;
        }


        if (parametr == LevelSettings::rowCount())
        {
            findRowCount = true;
            if (Checker::checkDataValidation(Checker::Categories::size, parametr, values))
            {
                sizes.first = values[0].toInt();
            }
        }
        if (parametr == LevelSettings::columnCount())
        {
            findColumnCount = true;
            if (Checker::checkDataValidation(Checker::Categories::size, parametr, values))
            {
                sizes.second = values[0].toInt();
            }
        }


        if (findRowCount && findColumnCount)
        {
            break;
        }
    }

    QString errorMessage = "Dont find parameter: ";
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

    while (!m_file.atEnd())
    {
        QString line = m_file.readLine();
        if (line.isEmpty())
        {
            continue;
        }

        QStringList values;
        FileParser::getLevelData(line, values);

        if (Checker::checkDataValidation(Checker::Categories::additionData, "additional level data value", values))
        {
            if (!Checker::is3ParametresInAdditionalLine(values))
            {
                qCritical() << "Error in addition color condition. "
                            << "Must have only 3 arguments in line: " << line;
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

    QString line;
    while (!m_file.atEnd())
    {
        line = m_file.readLine();
        FileParser::deleteBadSymbols(line);
        if (!line.isEmpty())
        {
            break;
        }
    }

    QStringList values;
    FileParser::getLevelData(line, values);

    if (Checker::checkDataValidation(Checker::Categories::levelData, "level data value", values))
    {
        condition.reserve(values.size());
        for (const QString& value : values)
        {
            condition.push_back(value.toInt());
        }
    }

    if (condition.empty())
    {
        qCritical() << "Not find condition to" << " "
                    << (isColumn ? "column" : "line") << " "
                    << "condition number: " << lineIndex;
    }
    return condition;
}

QVarLengthArray<std::optional<QColor>, 3> LevelLoader::getColors()
{
    QVarLengthArray<std::optional<QColor>, 3> colors;  // undef white black
    colors.resize(3);
    enum class Color { undefined, white, black };

    bool findUndefine = false, findWhite = false, findBlack = false;
    while (!m_file.atEnd())
    {
        QString parametr;
        QStringList values;

        QString line = m_file.readLine();
        FileParser::getSettingsData(line, parametr, values);

        if (!Checker::is1SettingsInLine(values))
        {
            qCritical() << "Not 1 settings in line: " << line;
        }


        if (parametr == LevelSettings::colorUndefined())
        {
            findUndefine = true;
            if (Checker::checkDataValidation(Checker::Categories::color, parametr, values))
            {
                colors[static_cast<int>(Color::undefined)] = QColor::fromString(values[0]);
            }
        }
        if (parametr == LevelSettings::colorWhite())
        {
            findWhite = true;
            if (Checker::checkDataValidation(Checker::Categories::color, parametr, values))
            {
                colors[static_cast<int>(Color::white)] = QColor::fromString(values[0]);
            }
        }
        if (parametr == LevelSettings::colorBlack())
        {
            findBlack = true;
            if (Checker::checkDataValidation(Checker::Categories::color, parametr, values))
            {
                colors[static_cast<int>(Color::black)] = QColor::fromString(values[0]);
            }
        }


        if (findWhite && findBlack && findUndefine)
        {
            break;
        }
    }

    QString errorMessage = "Dont find parameter: ";
    if (!findUndefine)
    {
        //qMessage() << errorMessage << LevelSettings::colorUndefined();
        colors[static_cast<int>(Color::undefined)] = std::nullopt;
    }
    if (!findWhite)
    {
        //qMessage() << errorMessage << LevelSettings::colorWhite();
        colors[static_cast<int>(Color::white)] = std::nullopt;
    }
    if (!findBlack)
    {
        //qMessage() << errorMessage << LevelSettings::colorBlack();
        colors[static_cast<int>(Color::black)] = std::nullopt;
    }

    return colors;
}
