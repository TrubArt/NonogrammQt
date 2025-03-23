#ifndef LEVELCHANGEDIALOG_H
#define LEVELCHANGEDIALOG_H

#include <QDialog>

namespace Ui
{
class LevelChangeDialog;
}

class LevelsDirectory;

class LevelChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelChangeDialog(const QString& lastLvlName, const QList<QString>& lvlNames, QWidget* parent = nullptr);
    ~LevelChangeDialog() override;

    const QString& getChosenLevelName() const;

private:
    void connectInitialization();
    void setLevels(const QList<QString>& lvlNames);
    void nameChanged();

    Ui::LevelChangeDialog* ui;
    QString m_chosenLvlName;
};

#endif // LEVELCHANGEDIALOG_H
