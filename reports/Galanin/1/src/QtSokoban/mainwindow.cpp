#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->WinWidth, this->WinHeight);
    this->Make1Level();
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
        if (this->yPlayer != 0)
        {

            if (this->map[this->xPlayer][this->yPlayer - 1] == box && this->map[this->xPlayer][this->yPlayer - 2] != wall)
            {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->yPlayer -= 1;
                this->map[this->xPlayer][this->yPlayer] = player;
                this->map[this->xPlayer][this->yPlayer - 1] = box;
            }
            else if (this->map[this->xPlayer][this->yPlayer - 1] != wall && this->map[this->xPlayer][this->yPlayer - 1] == floor)
            {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->yPlayer -= 1;
                this->map[this->xPlayer][this->yPlayer] = player;
            }
        }
    }
    else if(e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
    {
        if (this->xPlayer != this->length - 1)
        {
            if (this->map[this->xPlayer + 1][this->yPlayer] == box && this->map[this->xPlayer + 2][this->yPlayer] != wall)
            {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->xPlayer += 1;
                this->map[this->xPlayer][this->yPlayer] = player;
                this->map[this->xPlayer + 1][this->yPlayer] = box;
            }
            else if (this->map[this->xPlayer + 1][this->yPlayer] != wall  && this->map[this->xPlayer + 1][this->yPlayer] == floor)
            {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->xPlayer += 1;
                this->map[this->xPlayer][this->yPlayer] = player;
            }
        }
    }
    else if(e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
    {
        if (this->yPlayer != this->length - 1)
        {
            if (this->map[this->xPlayer][this->yPlayer + 1] == box && this->map[this->xPlayer][this->yPlayer + 2] != wall)
            {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->yPlayer += 1;
                this->map[this->xPlayer][this->yPlayer] = player;
                this->map[this->xPlayer][this->yPlayer + 1] = box;
            }
            else if (this->map[this->xPlayer][this->yPlayer + 1] != wall && this->map[this->xPlayer][this->yPlayer + 1] == floor)
            {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->yPlayer += 1;
                this->map[this->xPlayer][this->yPlayer] = player;
            }
        }
    }
    else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_A)
    {
        if (this->xPlayer != 0)
        {
            if (this->map[this->xPlayer - 1][this->yPlayer] == box && this->map[this->xPlayer - 2][this->yPlayer] != wall)
            {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->xPlayer -= 1;
                this->map[this->xPlayer][this->yPlayer] = player;
                this->map[this->xPlayer - 1][this->yPlayer] = box;
            }
            else if (this->map[this->xPlayer - 1][this->yPlayer] != wall && this->map[this->xPlayer - 1][this->yPlayer] == floor) {
                this->map[this->xPlayer][this->yPlayer] = floor;
                this->xPlayer -= 1;
                this->map[this->xPlayer][this->yPlayer] = player;
            }
        }
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
            if (this->finishMap[i][j] == finish)
            {
                path = ":/img/_pics/finish.png";
            }

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

            QPixmap pixmap(path);
            painter->drawPixmap(x*i, y*j, x, y, pixmap);
        }
    }
}
