#include "datalevelchange.h"
#include "ui_conditionlevelcreate.h"
#include "../utils.h"

DataLevelChange::DataLevelChange(const QString& changedLevelName,
                                 const std::shared_ptr<LevelData> levelData,
                                 const QStringList& levelsName,
                                 QWidget* parent)
    : ConditionLevelCreate(levelsName, parent)
    , m_originalName(changedLevelName)
{
    setWindowTitle(tr("Level Change"));

    fillFirstPage(changedLevelName, levelData);
    remakeScrollAreaSource();
    fillConditions(levelData);
    fillAdditions(levelData);
}

bool DataLevelChange::nameCheck()
{
    QString newName = ui->levelName->text();
    if (newName.isEmpty())
    {
        ui->levelName->setStyleSheet(Styles::lineEditEr());
        utils::sendMessage(m_errorWindowName, m_nameIsEmptyError);
        return false;
    }
    if (m_levelsName.contains(newName) && newName != m_originalName)
    {
        ui->levelName->setStyleSheet(Styles::lineEditEr());
        utils::sendMessage(m_errorWindowName, m_nameExistError);
        return false;
    }

    ui->levelName->setStyleSheet(Styles::lineEditNorm());
    return true;
}

void DataLevelChange::fillFirstPage(const QString& levelName, const std::shared_ptr<LevelData> levelData)
{
    ui->levelName->setText(levelName);
    ui->rows->setValue(levelData->properties.rowCount);
    ui->columns->setValue(levelData->properties.columnCount);
}

void DataLevelChange::fillConditions(const std::shared_ptr<LevelData> levelData)
{
    QStringList rowInfo = convertConditionToStr(levelData->data.lineConditions);
    writeConditionInfoToUI(rowInfo, m_linesContents->getConditions());

    QStringList columnInfo = convertConditionToStr(levelData->data.columnConditions);
    writeConditionInfoToUI(columnInfo, m_columnsContents->getConditions());
}

void DataLevelChange::fillAdditions(const std::shared_ptr<LevelData> levelData)
{
    std::vector<DataInformation::additionCondLine> addConditions = levelData->data.additionConditions;
    int countAddConditions = addConditions.size();

    if (countAddConditions == 0)
    {
        return;
    }

    m_additionContents->updateContent(countAddConditions);
    ui->pbDelete->setEnabled(true);
    const QVector<ConditionElement*>& condUI = m_additionContents->getConditions();

    DataInformation::additionCondLine oneCond;
    for (int indexCond = 0; indexCond < countAddConditions; ++indexCond)
    {
        oneCond = addConditions[indexCond];
        QString value = LevelData::createAdditionStrLine(oneCond);
        condUI[indexCond]->setText(value);
    }
}

QStringList DataLevelChange::convertConditionToStr(const std::vector<DataInformation::conditionLine>& cond) const
{
    QStringList conditions;
    for (const DataInformation::conditionLine& oneCond : cond)
    {
        QString value = LevelData::createConditionStrLine(std::move(oneCond));
        conditions.push_back(value);
    }
    return conditions;
}

void DataLevelChange::writeConditionInfoToUI(const QStringList& condString, const QVector<ConditionElement*>& condUI)
{
    int size = condString.size();
    for (int i = 0; i < size; ++i)
    {
        condUI[i]->setText(condString[i]);
    }
}
