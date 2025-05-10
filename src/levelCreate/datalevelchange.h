#ifndef DATALEVELCHANGE_H
#define DATALEVELCHANGE_H

#include "conditionlevelcreate.h"

class DataLevelChange : public ConditionLevelCreate
{
public:
    DataLevelChange(const QString& changedLevelName, const std::shared_ptr<LevelData> levelData,
                    const QStringList& levelsName, QWidget* parent = nullptr);

private:
    void fillFirstPage(const QString& levelName, const std::shared_ptr<LevelData> levelData);
    void fillConditions(const std::shared_ptr<LevelData> levelData);
    void fillAdditions(const std::shared_ptr<LevelData> levelData);

    void addValueToStr(QString& str, size_t value) const;
    QStringList convertConditionToStr(std::vector<DataInformation::conditionLine> cond) const;
    void writeConditionInfoToUI(const QStringList& condString, const QVector<ConditionElement*>& condUI);
};

#endif // DATALEVELCHANGE_H
