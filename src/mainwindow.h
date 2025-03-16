#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <qgraphicsview.h>

#include "table.h"
#include "queueCells/cellQueue.h"
#include "solution.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
    void repaintTable(int rowCount, int columnCount);
    void paintCell(const PaintCellInfo& cellInfo);

public slots:
    void changeNonogram();
    void actiontResetTableCells();

    void actionExit();
    void actionStartSolution();
    void actionChangeLevel();

signals:
    void changeNon();

private:
    void connectInitialization();
    void drawCellsFromQueue();

    Ui::mainwindowClass* ui;

    QGraphicsView m_view;
    Table m_picture;

    Solution* mp_currSolution;
};

#endif // MAINWINDOW_H
