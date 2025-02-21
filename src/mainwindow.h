#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>

#include <qgraphicsscene.h>
#include <qgraphicsview.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	void setFieldsSize(int heightCountRect, int widthCountRect);

public slots:
	void handlerSpinBox(int index);

private:
	void createTable();
	void setRectSize();

	QPoint findPositionInScene(int heightIndex, int widthIndex) const;

	Ui::mainwindowClass ui;

	QGraphicsScene* mp_scene;
	QGraphicsView* mp_view;

	QSizeF m_rectSize;
	int m_widthCountRect;
	int m_heightCountRect;
};

#endif // MAINWINDOW_H
