#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowState(Qt::WindowState::WindowMaximized);

    mp_scene = new QGraphicsScene();
    mp_view = new QGraphicsView(this);
    ui.gridLayout->addWidget(mp_view, 0, 1, 1, 1);

    changeTableSize(15, 14);

    mp_view->setScene(mp_scene);
    //setCentralWidget(m_pView);

    ui.spinBox_heightNum->setMaximum(m_heightCountCell - 1);
    ui.spinBox_widthNum->setMaximum(m_widthCountCell - 1);

    connect(ui.spinBox_heightNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
    connect(ui.spinBox_widthNum, QSpinBox::valueChanged, this, MainWindow::handlerSpinBox);
}

MainWindow::~MainWindow()
{
    delete mp_scene;
    delete mp_view;
}

void MainWindow::setTableSize(int heightCountRect, int widthCountRect)
{
    m_heightCountCell = heightCountRect;
    m_widthCountCell = widthCountRect;
}

void MainWindow::createTable()
{
    QPen pen(Qt::black);
    QColor color(colors.getUndefine());

    for (int hIndex = 0; hIndex < m_heightCountCell; ++hIndex)
    {
        for (int wIndex = 0; wIndex < m_widthCountCell; ++wIndex)
        {
            addCell(hIndex, wIndex, pen, color);
        }
    }
}

void MainWindow::removeTable()
{
    for (int hIndex = 0; hIndex < m_heightCountCell; ++hIndex)
    {
        for (int wIndex = 0; wIndex < m_widthCountCell; ++wIndex)
        {
            removeCell(hIndex, wIndex);
        }
    }
}

void MainWindow::setCellSize()
{
    int sizeValue = 20;
    m_rectSize.setWidth(sizeValue);
    m_rectSize.setHeight(sizeValue);
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

QPoint MainWindow::findTopLeftPointCell(int heightIndex, int widthIndex) const
{
    QPoint answer(widthIndex * m_rectSize.width(), heightIndex * m_rectSize.height());
    return answer;
}

void MainWindow::paintCell(const PaintCellInfo& cellInfo)
{
    int hIndex = cellInfo.rowNumber;
    int wIndex = cellInfo.indexInRow;
    QColor col = colors.convertColorFromCore(cellInfo.color);

    removeCell(hIndex, wIndex);
    addCell(hIndex, wIndex, QPen(Qt::black), col);
}

void MainWindow::changeTableSize(int rowCount, int columnCount)
{
    removeTable();

    setTableSize(rowCount, columnCount);
    setCellSize();

    createTable();
}

QPoint MainWindow::findCenterCell(int heightIndex, int widthIndex) const
{
    QPoint cellLeftTop = findTopLeftPointCell(heightIndex, widthIndex);
    QPoint centerElem(cellLeftTop.x() + m_rectSize.width() / 2, cellLeftTop.y() + m_rectSize.height() / 2);
    return centerElem;
}

void MainWindow::removeCell(int heightIndex, int widthIndex)
{
    QPoint centerElem = findCenterCell(heightIndex, widthIndex);
    QGraphicsItem * elem = mp_scene->itemAt(centerElem, QTransform());
    mp_scene->removeItem(elem);
}

void MainWindow::addCell(int heightIndex, int widthIndex, const QPen& pen, const QColor& col)
{
    QPoint topleft = findTopLeftPointCell(heightIndex, widthIndex);
    QRectF rect(topleft, m_rectSize);
    mp_scene->addRect(rect, pen, QBrush(col));
}
