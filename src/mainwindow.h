#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <qgraphicsview.h>
#include <optional>
#include <QCloseEvent>

#include "table.h"
#include "queueCells/cellQueue.h"
#include "solution.h"
#include "levelsManager/levelsStorage.h"
#include "leftTab/tablelevels.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
    void paintCell(const PaintCellInfo& cellInfo);

public slots:
    void changeNonogram(const QString& lvlName);

    void actiontResetTableCells();
    void actionExit();
    void actionStartSolution();
    void actionChangeLevel();
    void actionSaveLevels();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void leftTabClicked(int index);
    void newLevelChoice(QTableWidgetItem *item);
    void deleteLevelHandler(const QString& levelName);

private:
    void viewInitialization();
    void connectInitialization();
    void drawCellsFromQueue(const std::vector<PaintCellInfo>& cells);

    Ui::mainwindowClass* ui;
    TableLevels* m_tableLevels_ui;

    QGraphicsView m_view;
    Table m_picture;

    LevelsStorage m_levelsStorage;
    std::optional<Solution> m_currSolution;
    QString m_currentLevelName;
};

#endif // MAINWINDOW_H
