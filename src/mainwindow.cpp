#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowState(Qt::WindowState::WindowMaximized);

    mp_view = new QGraphicsView(this);
    ui.gridLayout->addWidget(mp_view, 0, 1, 1, 1);

    changeTableSize(15, 14);

    mp_view->setScene(picture.get());
    //setCentralWidget(m_pView);

    ui.spinBox_heightNum->setMaximum(picture.getHeight() - 1);
    ui.spinBox_widthNum->setMaximum(picture.getWidth() - 1);

    connect(ui.spinBox_heightNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
    connect(ui.spinBox_widthNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
}

MainWindow::~MainWindow()
{
    delete mp_view;
}

void MainWindow::handlerSpinBox(int)
{
    // int hIndex = ui.spinBox_heightNum->value();
    // int wIndex = ui.spinBox_widthNum->value();
    // QPoint rectPoint = findLeftTopPointCell(hIndex, wIndex);

    // // findCenter of elem and delete them
    // QPoint centerElem(rectPoint.x() + m_rectSize.width() / 2, rectPoint.y() + m_rectSize.height() / 2);
    // QGraphicsItem * elem = mp_scene->itemAt(centerElem, QTransform());
    // mp_scene->removeItem(elem);

    // // add new elem with new brush
    // QRectF rect(rectPoint, m_rectSize);
    // mp_scene->addRect(rect, QPen(Qt::black), QBrush(Qt::blue));
}

void MainWindow::paintCell(const PaintCellInfo& cellInfo)
{
    int hIndex = cellInfo.rowNumber;
    int wIndex = cellInfo.indexInRow;

    picture.repaintCell(hIndex, wIndex, cellInfo.color);
}

void MainWindow::changeTableSize(int rowCount, int columnCount)
{
    picture.setTableSize(rowCount, columnCount);
}

