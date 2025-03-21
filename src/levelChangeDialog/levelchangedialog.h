#ifndef LEVELCHANGEDIALOG_H
#define LEVELCHANGEDIALOG_H

#include <QDialog>

namespace Ui
{
class LevelChangeDialog;
}

class LevelChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelChangeDialog(const QString& lastLvlName, QWidget* parent = nullptr);
    ~LevelChangeDialog() override;

    const QString& getChosenLevelName() const;

private:
    void connectInitialization();
    void setLevels();

    void nameChanged();

    Ui::LevelChangeDialog* ui;

    QString m_chosenLvlName;
};

#endif // LEVELCHANGEDIALOG_H
