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
    explicit LevelChangeDialog(const QString& lastLvlName, const LevelsStorage::dataType& lvlsData, QWidget* parent = nullptr);
    ~LevelChangeDialog() override;

    const QString& getChosenLevelName() const;
    const QMap<QString, PropertiesInformation>& getProperties() const;

public slots:
    void nameChanged();
    void changeBlackColor();
    void changeWhiteColor();
    void changeUndefinedColor();
    void resetColorToDefault();

private:
    enum class ColumnsName { name, size };

    // initial functions
    void createPropertiesData(const LevelsStorage::dataType& lvlsData);
    void setLevels();
    void connectInitialization();
    void setPreviousLevelName(const QString& prevName);
    void createTableUI();
    void updateSettingsViewUI();

    //
    void paintColorSetting(QPushButton* button, const QColor& color);


    Ui::LevelChangeDialog* ui;
    QMap<QString, PropertiesInformation> m_propertiesData;

    QString m_chosenLvlName;
};

#endif // LEVELCHANGEDIALOG_H
