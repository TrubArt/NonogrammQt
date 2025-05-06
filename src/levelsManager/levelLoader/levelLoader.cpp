#include "levelLoader.h"

#include <memory>
#include <QDebug>

#include "fileParser.h"
#include "checker.h"

void LevelLoader::setFile(const std::string& fileName)
{
    m_file.close();

    m_file.setFileName(QString::fromStdString(fileName));
    if (!m_file.open(QIODevice::ReadWrite))
    {
        qCritical() << "File " << fileName << " not open!";
    }
}

std::string LevelLoader::getFileName() const
{
    return m_file.fileName().toStdString();
}

void LevelLoader::messageFindBadParameter(const QString& specialization, const QString& value)
{
    qCritical() << "Bad values!"
                << " Parameter: " << specialization
                << " Value: " << value;
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
            QString rowSize = values[0];
            if (Checker::checkDataValidation(Checker::Categories::size, rowSize))
            {
                sizes.first = rowSize.toInt();
            }
            else
            {
                messageFindBadParameter(parametr, rowSize);
            }
        }
        else if (parametr == LevelSettings::columnCount())
        {
            findColumnCount = true;
            QString columnSize = values[0];
            if (Checker::checkDataValidation(Checker::Categories::size, columnSize))
            {
                sizes.second = columnSize.toInt();
            }
            else
            {
                messageFindBadParameter(parametr, columnSize);
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
        FileParser::deleteBadSymbols(line);
        if (line.isEmpty())
        {
            continue;
        }

        QStringList values;
        FileParser::getLevelData(line, values);

        if (!Checker::is3ParametresInAdditionalLine(values))
        {
            qCritical() << "Error in addition color condition. "
                        << "Must have only 3 arguments in line: " << line;
        }

        std::array<size_t, 3> oneAdditionalCondition;
        for (int i = 0; i < 3; ++i)
        {
            QString value = values[i];
            if (Checker::checkDataValidation(Checker::Categories::additionData, value))
            {
                oneAdditionalCondition[i] = value.toInt();
            }
            else
            {
                messageFindBadParameter("additional level data value", value);
            }
        }

        condition.push_back(oneAdditionalCondition);
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


    condition.reserve(values.size());
    for (const QString& value : values)
    {
        if (Checker::checkDataValidation(Checker::Categories::levelData, value))
        {
            condition.push_back(value.toInt());
        }
        else
        {
            messageFindBadParameter("level data value", value);
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

QVarLengthArray<std::optional<QColor>, 3> LevelLoader::getNonogramColors()
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
            QString undefColor = values[0];
            if (Checker::checkDataValidation(Checker::Categories::color, undefColor))
            {
                colors[static_cast<int>(Color::undefined)] = QColor::fromString(undefColor);
            }
            else
            {
                messageFindBadParameter(parametr, undefColor);
            }
        }
        else if (parametr == LevelSettings::colorWhite())
        {
            findWhite = true;
            QString whiteColor = values[0];
            if (Checker::checkDataValidation(Checker::Categories::color, whiteColor))
            {
                colors[static_cast<int>(Color::white)] = QColor::fromString(whiteColor);
            }
            else
            {
                messageFindBadParameter(parametr, whiteColor);
            }
        }
        else if (parametr == LevelSettings::colorBlack())
        {
            findBlack = true;
            QString blackColor = values[0];
            if (Checker::checkDataValidation(Checker::Categories::color, blackColor))
            {
                colors[static_cast<int>(Color::black)] = QColor::fromString(blackColor);
            }
            else
            {
                messageFindBadParameter(parametr, blackColor);
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

void LevelLoader::saveProperty(const QString& category, const QString& value)
{
    QTextStream out(&m_file);
    out << category << FileParser::m_separatorForSettings << "\t\t" << value << "\n";
}

void LevelLoader::saveData(const QString& lineData)
{
    QTextStream out(&m_file);
    out << lineData << "\n";
}
