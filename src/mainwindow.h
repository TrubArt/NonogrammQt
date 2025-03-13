#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>

#include <qgraphicsview.h>

#include "table.h"
#include "queueCells/cellQueue.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
    void changeTableSize(int rowCount, int columnCount);
    void paintCell(const PaintCellInfo& cellInfo);

public slots:
	void handlerSpinBox(int index);

private:
	Ui::mainwindowClass ui;

	QGraphicsView* mp_view;
    Table m_picture;
};

#endif // MAINWINDOW_H
