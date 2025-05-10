#include "levelManager.h"
#include "levelLoader/levelLoader.h"

LevelManager::LevelManager()
    : ILoadManager(new LevelLoader())
{}

void LevelManager::setDirectoryAndData(const QDir& dir, std::shared_ptr<LevelData> loadedData)
{
    m_levelDir = dir;
    m_loadedData = loadedData;
}

void LevelManager::returnToDefault()
{
    setDirectoryAndData(QDir(), nullptr);
    fileLoader->setFile("");
}

std::pair<size_t, size_t> LevelManager::getNonogramSize()
{
    if (m_loadedData)
    {
        return { m_loadedData->properties.rowCount, m_loadedData->properties.columnCount };
    }

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + infoDataFile;
    fileLoader->setFile(fullpath.toStdString());
    return fileLoader->getNonogramSize();
}

ColorStore LevelManager::getNonogramColors()
{
    if (m_loadedData)
    {
        return m_loadedData->properties.colors;
    }

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + infoDataFile;
    fileLoader->setFile(fullpath.toStdString());
    QVarLengthArray<std::optional<QColor>, 3> colorsArray = static_cast<LevelLoader*>(fileLoader.get())->getNonogramColors();

    ColorStore colors;
    if (colorsArray[0])
    {
        colors.setUndefine(colorsArray[0].value());
    }
    if (colorsArray[1])
    {
        colors.setWhite(colorsArray[1].value());
    }
    if (colorsArray[2])
    {
        colors.setBlack(colorsArray[2].value());
    }
    return colors;
}

std::vector<std::array<size_t, 3>> LevelManager::getAdditionalCondition()
{
    if (m_loadedData->isLoadedDataInformation)
    {
        return m_loadedData->data.additionConditions;
    }

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + additionDataFile;
    fileLoader->setFile(fullpath.toStdString());
    std::vector<std::array<size_t, 3>> additionInfo = fileLoader->getAdditionalCondition();

    m_loadedData->data.additionConditions = additionInfo;
    return additionInfo;
}

std::vector<size_t> LevelManager::getLineSequence(bool isColumn, size_t lineIndex)
{
    if (m_loadedData->isLoadedDataInformation)
    {
        if (isColumn)
        {
            return m_loadedData->data.columnConditions[lineIndex];
        }

        return m_loadedData->data.lineConditions[lineIndex];
    }

    std::string fullpath = (m_levelDir.absolutePath() + "/" + conditionDataFile).toStdString();
    if (fileLoader->getFileName() != fullpath)
    {
        fileLoader->setFile(fullpath);
    }
    std::vector<size_t> condition = fileLoader->getLineSequence(isColumn, lineIndex);

    if (isColumn)
    {
        m_loadedData->data.columnConditions[lineIndex] = condition;
    }
    else
    {
        m_loadedData->data.lineConditions[lineIndex] = condition;
    }

    return condition;
}

void LevelManager::saveAll()
{
    if (!m_levelDir.exists())
    {
        qDebug() << "Create new level: " << m_levelDir.dirName();
        m_levelDir.mkpath(".");
    }
    saveProperties();
    saveData();
}

void LevelManager::saveProperties()
{
    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + infoDataFile;
    QFile::remove(fullpath);
    fileLoader->setFile(fullpath.toStdString());

    LevelLoader* loader = static_cast<LevelLoader*>(fileLoader.get());
    loader->saveProperty(LevelSettings::rowCount(), QString::number(m_loadedData->properties.rowCount));
    loader->saveProperty(LevelSettings::columnCount(), QString::number(m_loadedData->properties.columnCount));
    loader->saveProperty(LevelSettings::colorUndefined(), m_loadedData->properties.colors.getUndefine().name());
    loader->saveProperty(LevelSettings::colorWhite(), m_loadedData->properties.colors.getWhite().name());
    loader->saveProperty(LevelSettings::colorBlack(), m_loadedData->properties.colors.getBlack().name());
}

void LevelManager::saveData()
{
    if (!m_loadedData->isLoadedDataInformation)
    {
        return;
    }

    auto createConditionLine = [](const std::vector<size_t>& lineData, int countForReserve) -> QString
    {
        QString data;
        data.reserve(countForReserve);
        for (int i = 0; i < lineData.size(); ++i)
        {
            if (i != 0)
            {
                data += " ";
            }
            data += QString::number(lineData[i]);
        }
        return data;
    };

    LevelLoader* loader = static_cast<LevelLoader*>(fileLoader.get());
    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + conditionDataFile;
    QFile::remove(fullpath);
    fileLoader->setFile(fullpath.toStdString());

    for (const std::vector<size_t>& lineData : m_loadedData->data.lineConditions)
    {
        int reserve = lineData.size() * 3; // *3 из расчёта что одно число оптимально двузначное + пробелы между каждым числом
        loader->saveData(createConditionLine(lineData, reserve));
    }
    loader->saveData("");
    for (const std::vector<size_t>& lineData : m_loadedData->data.columnConditions)
    {
        int reserve = lineData.size() * 3; // *3 из расчёта что одно число оптимально двузначное + пробелы между каждым числом
        loader->saveData(createConditionLine(lineData, reserve));
    }


    fullpath = m_levelDir.absolutePath() + QDir::separator() + additionDataFile;
    QFile::remove(fullpath);
    fileLoader->setFile(fullpath.toStdString());

    for (const std::array<size_t, 3>& lineData : m_loadedData->data.additionConditions)
    {
        QString line;
        line.reserve(9); // 9 из расчёта что размер нонограммы 3-х значеное число оптимально + 2 пробела + 1 на цвет
        line += QString::number(lineData[0]) + " ";
        line += QString::number(lineData[1]) + " ";
        line += QString::number(lineData[2]);
        loader->saveData(line);
    }
}
