#ifndef LEVELCHANGEDIALOG_H
#define LEVELCHANGEDIALOG_H

#include <QDialog>
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
    explicit LevelChangeDialog(const QString& lastLvlName, const LevelsStorage::dataType& lvlsData, QWidget* parent = nullptr);
    ~LevelChangeDialog() override;

    const QString& getChosenLevelName() const;

private:
    enum class ColumnsName { name, size };

    void setLevels(const LevelsStorage::dataType& lvlsData);
    void createTableUI(const LevelsStorage::dataType& lvlsData);
    void connectInitialization();
    void nameChanged();

    Ui::LevelChangeDialog* ui;
    QString m_chosenLvlName;
};

#endif // LEVELCHANGEDIALOG_H
