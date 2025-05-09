#ifndef TABLELEVELS_H
#define TABLELEVELS_H

#include <QWidget>
#include <QTableWidgetItem>

#include "../levelsManager/levelsStorage.h"

namespace Ui
{
class TableLevels;
}

class TableLevels : public QWidget
{
    Q_OBJECT

signals:
    void newLevelChoice(QTableWidgetItem *item);

public:
    explicit TableLevels(LevelsStorage& levelsStorage, QWidget* parent = nullptr);
    ~TableLevels() override;

public slots:
    void condionsLevelCreate();
    void deleteLevel();

private slots:
    void selectionChanged();

private:
    enum class ColumnsName { name, size };

    void addLevelView(int insertIndex, const QString& name, int rowCount, int columnCount);
    void connectInitialization();

    Ui::TableLevels* ui;
    LevelsStorage& m_levels;
};

#endif // TABLELEVELS_H
