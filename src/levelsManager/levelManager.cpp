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

ColorStore LevelManager::getColors()
{
    if (m_loadedData)
    {
        return ColorStore(m_loadedData->properties.colors);
    }

    QString fullpath = m_levelDir.absolutePath() + QDir::separator() + infoDataFile;
    fileLoader->setFile(fullpath.toStdString());
    QVarLengthArray<std::optional<QColor>, 3> colorsArray = static_cast<LevelLoader*>(fileLoader.get())->getColors();

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
