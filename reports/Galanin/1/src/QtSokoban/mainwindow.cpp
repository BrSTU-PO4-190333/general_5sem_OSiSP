#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->WinWidth, this->WinHeight);

    this->generate1Level();

    auto timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(100);
}

void MainWindow::animate()
{
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up || e->key() == Qt::Key_W)
    {
        this->goTop();
    }
    else if(e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
    {
        this->goRight();
    }
    else if(e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
    {
        this->goBottom();
    }
    else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_A)
    {
        this->goLeft();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    this->sayWon();
    this->drawAxes(&painter);
    this->drawTextures(&painter);
}
