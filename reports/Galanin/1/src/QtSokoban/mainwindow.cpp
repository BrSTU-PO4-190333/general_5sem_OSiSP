#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->WinWidth, this->WinHeight);
    this->Make1Level();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up || e->key() == Qt::Key_W)
    {

    }
    else if(e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
    {

    }
    else if(e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
    {

    }
    else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_A)
    {

    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    this->drawAxes(&painter);
    this->drawTextures(&painter);
}

void MainWindow::drawAxes(QPainter *painter)
{
    int x = this->WinWidth / this->length;
    int y = this->WinHeight / this->length;
    for (int i = 0; i < this->length; i += 1)
    {
        for (int j = 0; j < this->length; j += 1)
        {
            QRect rect(x*i, y*j, x, y);
            painter->drawRect(rect);
        }
    }
}

void MainWindow::drawTextures(QPainter *painter)
{
    int x = this->WinWidth / this->length;
    int y = this->WinHeight / this->length;
    for (int i = 0; i < this->length; i += 1)
    {
        for (int j = 0; j < this->length; j += 1)
        {
            QString path = ":/img/_pics/err.png";
            if (this->map[i][j] == floor)
            {
                path = ":/img/_pics/floor.png";
            }
            else if (this->map[i][j] == wall)
            {
                path = ":/img/_pics/wall.png";
            }
            else if (this->map[i][j] == player)
            {
                path = ":/img/_pics/player.png";
            }
            else if (this->map[i][j] == box)
            {
                path = ":/img/_pics/box.png";
            }
            else if (this->map[i][j] == finish)
            {
                path = ":/img/_pics/finish.png";
            }
            QPixmap pixmap(path);
            painter->drawPixmap(x*i, y*j, x, y, pixmap);
        }
    }
}
