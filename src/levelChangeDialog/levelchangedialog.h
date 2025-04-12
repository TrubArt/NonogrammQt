#ifndef LEVELCHANGEDIALOG_H
#define LEVELCHANGEDIALOG_H

#include <QDialog>
#include <QLabel>
#include "../levelsManager/levelsStorage.h"

namespace Ui
{
class LevelChangeDialog;
}

class LevelsDirectory;

class LevelChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelChangeDialog(const QString& lastLvlName, LevelsStorage::dataType& lvlsData, QWidget* parent = nullptr);
    ~LevelChangeDialog() override;

    const QString& getChosenLevelName() const;

private:
    enum class ColumnsName { name, size };

    void setLevels();
    void createTableUI();

    void paintColorSetting(QLabel* label, const QColor& color);
    void updateSettingsViewUI();

    void connectInitialization();
    void setPreviousLevelName(const QString& prevName);

    void nameChanged();

    Ui::LevelChangeDialog* ui;
    LevelsStorage::dataType& m_levelsData;

    QString m_chosenLvlName;
};

#endif // LEVELCHANGEDIALOG_H
