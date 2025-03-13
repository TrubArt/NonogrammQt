#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_picture()
{
    ui.setupUi(this);
    setWindowState(Qt::WindowState::WindowMaximized);

    mp_view = new QGraphicsView(this);
    ui.gridLayout->addWidget(mp_view, 0, 1, 1, 1);

    changeTableSize(24, 24);

    mp_view->setScene(m_picture.get());
    //setCentralWidget(m_pView);

    ui.spinBox_heightNum->setMaximum(m_picture.getHeight() - 1);
    ui.spinBox_widthNum->setMaximum(m_picture.getWidth() - 1);

    connect(ui.spinBox_heightNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
    connect(ui.spinBox_widthNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
}

MainWindow::~MainWindow()
{
    delete mp_view;
}

void MainWindow::handlerSpinBox(int)
{
    // STUB
}

void MainWindow::paintCell(const PaintCellInfo& cellInfo)
{
    int hIndex = cellInfo.rowNumber;
    int wIndex = cellInfo.indexInRow;

    m_picture.repaintCell(hIndex, wIndex, cellInfo.color);
}

void MainWindow::changeTableSize(int rowCount, int columnCount)
{
    m_picture.setTableSize(rowCount, columnCount);
}

