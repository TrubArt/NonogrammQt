#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>

#include <qgraphicsscene.h>
#include <qgraphicsview.h>

#include "colorstore.h"
#include "queueCells/cellQueue.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
    void changeTableSize(int rowCount, int columnCount);
    void paintCell(const PaintCellInfo& cellInfo);

public slots:
	void handlerSpinBox(int index);

private:
    void setCellSize();
    void createTable();
    void removeTable();
    void setTableSize(int heightCountRect, int widthCountRect);

    QPoint findTopLeftPointCell(int heightIndex, int widthIndex) const;
    QPoint findCenterCell(int heightIndex, int widthIndex) const;

    void addCell(int heightIndex, int widthIndex, const QPen& pen, const QColor& col);
    void removeCell(int heightIndex, int widthIndex);

	Ui::mainwindowClass ui;

	QGraphicsScene* mp_scene;
	QGraphicsView* mp_view;

	QSizeF m_rectSize;
    int m_widthCountCell;
    int m_heightCountCell;
    ColorStore colors;
};

#endif // MAINWINDOW_H
