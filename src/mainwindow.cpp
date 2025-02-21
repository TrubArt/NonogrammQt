#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowState(Qt::WindowState::WindowMaximized);

    mp_scene = new QGraphicsScene();
    mp_view = new QGraphicsView(this);
    ui.gridLayout->addWidget(mp_view, 0, 1, 1, 1);

    setFieldsSize(10, 20);
    setRectSize();
    createTable();

    mp_view->setScene(mp_scene);
    //setCentralWidget(m_pView);

    ui.spinBox_heightNum->setMaximum(m_heightCountRect - 1);
    ui.spinBox_widthNum->setMaximum(m_widthCountRect - 1);

    connect(ui.spinBox_heightNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
    connect(ui.spinBox_widthNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
}

MainWindow::~MainWindow()
{
    delete mp_scene;
    delete mp_view;
}

void MainWindow::setFieldsSize(int heightCountRect, int widthCountRect)
{
    m_widthCountRect = widthCountRect;
    m_heightCountRect = heightCountRect;
}

void MainWindow::createTable()
{
    QPen pen(Qt::black);
    QBrush brush(Qt::gray);

    for (int hIndex = 0; hIndex < m_heightCountRect; ++hIndex)
    {
        for (int wIndex = 0; wIndex < m_widthCountRect; ++wIndex)
        {
            QPoint rectPoint = findPositionInScene(hIndex, wIndex);
            QRectF rect(rectPoint, m_rectSize);
            mp_scene->addRect(rect, pen, brush);
        }
    }
}

void MainWindow::setRectSize()
{
    int sizeValue = 20;
    m_rectSize.setWidth(sizeValue);
    m_rectSize.setHeight(sizeValue);
}

void MainWindow::handlerSpinBox(int)
{
    int hIndex = ui.spinBox_heightNum->value();
    int wIndex = ui.spinBox_widthNum->value();
    QPoint rectPoint = findPositionInScene(hIndex, wIndex);

    // findCenter of elem and delete them
    QPoint centerElem(rectPoint.x() + m_rectSize.width() / 2, rectPoint.y() + m_rectSize.height() / 2);
    QGraphicsItem * elem = mp_scene->itemAt(centerElem, QTransform());
    mp_scene->removeItem(elem);

    // add new elem with new brush
    QRectF rect(rectPoint, m_rectSize);
    mp_scene->addRect(rect, QPen(Qt::black), QBrush(Qt::blue));
}

QPoint MainWindow::findPositionInScene(int heightIndex, int widthIndex) const
{
    QPoint answer(widthIndex * m_rectSize.width(), heightIndex * m_rectSize.height());
    return answer;
}
