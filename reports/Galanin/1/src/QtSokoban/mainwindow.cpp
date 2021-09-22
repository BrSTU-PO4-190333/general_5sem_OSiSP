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
            MapChar f0 = this->map[this->xPlayer][this->yPlayer];
            MapChar f1 = this->map[this->xPlayer][this->yPlayer - 1];
            MapChar f2 = this->map[this->xPlayer][this->yPlayer - 2];

            // player -> floor
            // floor  -> player
            if (f0 == player && f1 == floor)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = player;

                return;
            }

            // finPlayer -> floor
            // finish    -> player
            if (f0 == finPlayer && f1 == floor)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = player;

                return;
            }

            // player -> box    -> floor
            // floor  -> player -> box
            if (f0 == player && f1 == box && f2 == floor)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer - 1] = box;

                return;
            }

            // finPlayer -> box    -> floor
            // finish    -> player -> box
            if (f0 == finPlayer && f1 == box && f2 == floor)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer - 1] = box;

                return;
            }

            // player -> box    -> finish
            // floor  -> player -> finBox
            if (f0 == player && f1 == box && f2 == finish)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer - 1] = finBox;

                return;
            }

            // finPlayer -> box    -> finish
            // finish    -> player -> finBox
            if (f0 == finPlayer && f1 == box && f2 == finish)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer - 1] = finBox;

                return;
            }

            // player -> finBox    -> floor
            // floor  -> finPlayer -> box
            if (f0 == player && f1 == finBox && f2 == floor)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer - 1] = box;

                return;
            }

            // finPlayer -> finBox    -> floor
            // finish    -> finPlayer -> box
            if (f0 == finPlayer && f1 == finBox && f2 == floor)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer - 1] = box;

                return;
            }

            // player -> finBox    -> finish
            // floor  -> finPlayer -> finBox
            if (f0 == player && f1 == finBox && f2 == finish)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer - 1] = finBox;
                return;
            }

            // finPlayer -> finBox    -> finish
            // finish    -> finPlayer -> finBox
            if (f0 == finPlayer && f1 == finBox && f2 == finish)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer - 1] = finBox;
                return;
            }

            // player -> finish
            // floor  -> finPlayer
            if (f0 == player && f1 == finish)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                return;
            }

            // finPlayer -> finish
            // finish    -> finPlayer
            if (f0 == finPlayer && f1 == finish)
            {
                this->yPlayer -= 1;

                this->map[this->xPlayer][this->yPlayer + 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                return;
            }
        }
    }
    else if(e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
    {
        if (this->xPlayer != this->length - 1)
        {
            MapChar f0 = this->map[this->xPlayer    ][this->yPlayer];
            MapChar f1 = this->map[this->xPlayer + 1][this->yPlayer];
            MapChar f2 = this->map[this->xPlayer + 2][this->yPlayer];

            // player -> floor
            // floor  -> player
            if (f0 == player && f1 == floor)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = player;

                return;
            }

            // finPlayer -> floor
            // finish    -> player
            if (f0 == finPlayer && f1 == floor)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = player;

                return;
            }

            // player -> box    -> floor
            // floor  -> player -> box
            if (f0 == player && f1 == box && f2 == floor)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer + 1][this->yPlayer] = box;

                return;
            }

            // finPlayer -> box    -> floor
            // finish    -> player -> box
            if (f0 == finPlayer && f1 == box && f2 == floor)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer + 1][this->yPlayer] = box;

                return;
            }

            // finPlayer -> finBox -> floor
            // finish    -> finPlayer -> box
            if (f0 == finPlayer && f1 == finBox && f2 == floor)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer + 1][this->yPlayer] = box;

                return;
            }

            // player -> finBox    -> floor
            // floor  -> finPlayer -> box
            if (f0 == player && f1 == finBox && f2 == floor)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer + 1][this->yPlayer] = box;

                return;
            }

            // player -> box    -> finish
            // floor  -> player -> finBox
            if (f0 == player && f1 == box && f2 == finish)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer + 1][this->yPlayer] = finBox;

                return;
            }

            // finPlayer -> box    -> finish
            // finish    -> player -> finBox
            if (f0 == finPlayer && f1 == box && f2 == finish)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer + 1][this->yPlayer] = finBox;

                return;
            }

            // player -> finBox    -> finish
            // floor  -> finPlayer -> finBox
            if (f0 == player && f1 == finBox && f2 == finish)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer + 1][this->yPlayer] = finBox;
                return;
            }

            // finPlayer -> finBox    -> finish
            // finish    -> finPlayer -> finBox
            if (f0 == finPlayer && f1 == finBox && f2 == finish)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer + 1][this->yPlayer] = finBox;
                return;
            }

            // player -> finish
            // floor  -> finPlayer
            if (f0 == player && f1 == finish)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                return;
            }

            // finPlayer -> finish
            // finish    -> finPlayer
            if (f0 == finPlayer && f1 == finish)
            {
                this->xPlayer += 1;

                this->map[this->xPlayer - 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                return;
            }
        }
    }
    else if(e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
    {
        if (this->yPlayer != this->length - 1)
        {
            MapChar f0 = this->map[this->xPlayer][this->yPlayer];
            MapChar f1 = this->map[this->xPlayer][this->yPlayer + 1];
            MapChar f2 = this->map[this->xPlayer][this->yPlayer + 2];

            // player -> floor
            // floor  -> player
            if (f0 == player && f1 == floor)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = player;

                return;
            }

            // finPlayer -> floor
            // finish    -> player
            if (f0 == finPlayer && f1 == floor)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = player;

                return;
            }

            // player -> box    -> floor
            // floor  -> player -> box
            if (f0 == player && f1 == box && f2 == floor)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer + 1] = box;

                return;
            }

            // finPlayer -> box    -> floor
            // finish    -> player -> box
            if (f0 == finPlayer && f1 == box && f2 == floor)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer + 1] = box;

                return;
            }

            // player -> finBox    -> floor
            // floor  -> finPlayer -> box
            if (f0 == player && f1 == finBox && f2 == floor)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer + 1] = box;

                return;
            }

            // finPlayer -> finBox    -> floor
            // finish    -> finPlayer -> box
            if (f0 == finPlayer && f1 == finBox && f2 == floor)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer + 1] = box;

                return;
            }

            // player -> box    -> finish
            // floor  -> player -> finBox
            if (f0 == player && f1 == box && f2 == finish)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer + 1] = finBox;

                return;
            }

            // finPlayer -> box    -> finish
            // finish    -> player -> finBox
            if (f0 == finPlayer && f1 == box && f2 == finish)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = player;
                this->map[this->xPlayer][this->yPlayer + 1] = finBox;

                return;
            }

            // player -> finBox    -> finish
            // floor  -> finPlayer -> finBox
            if (f0 == player && f1 == finBox && f2 == finish)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer + 1] = finBox;
                return;
            }

            // finPlayer -> finBox    -> finish
            // finish    -> finPlayer -> finBox
            if (f0 == finPlayer && f1 == finBox && f2 == finish)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                this->map[this->xPlayer][this->yPlayer + 1] = finBox;
                return;
            }

            // player -> finish
            // floor  -> finPlayer
            if (f0 == player && f1 == finish)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = floor;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                return;
            }

            // finPlayer -> finish
            // finish    -> finPlayer
            if (f0 == finPlayer && f1 == finish)
            {
                this->yPlayer += 1;

                this->map[this->xPlayer][this->yPlayer - 1] = finish;
                this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
                return;
            }
        }
    }
    else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_A)
    {
        if (this->xPlayer != 0)
        {
            MapChar f0 = this->map[this->xPlayer    ][this->yPlayer];
            MapChar f1 = this->map[this->xPlayer - 1][this->yPlayer];
            MapChar f2 = this->map[this->xPlayer - 2][this->yPlayer];

            // player -> floor
            // floor  -> player
            if (f0 == player && f1 == floor)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = player;

                return;
            }

            // finPlayer -> floor
            // finish    -> player
            if (f0 == finPlayer && f1 == floor)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = player;

                return;
            }

            // player -> box    -> floor
            // floor  -> player -> box
            if (f0 == player && f1 == box && f2 == floor)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer - 1][this->yPlayer] = box;

                return;
            }

            // finPlayer -> box    -> floor
            // finish    -> player -> box
            if (f0 == finPlayer && f1 == box && f2 == floor)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer - 1][this->yPlayer] = box;

                return;
            }

            // player -> finBox    -> floor
            // floor  -> finPlayer -> box
            if (f0 == player && f1 == finBox && f2 == floor)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer - 1][this->yPlayer] = box;

                return;
            }

            // finPlayer -> finBox    -> floor
            // finish    -> finPlayer -> box
            if (f0 == finPlayer && f1 == finBox && f2 == floor)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer - 1][this->yPlayer] = box;

                return;
            }

            // player -> box    -> finish
            // floor  -> player -> finBox
            if (f0 == player && f1 == box && f2 == finish)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer - 1][this->yPlayer] = finBox;

                return;
            }

            // finPlayer -> box    -> finish
            // finish    -> player -> finBox
            if (f0 == finPlayer && f1 == box && f2 == finish)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = player;
                this->map[this->xPlayer - 1][this->yPlayer] = finBox;

                return;
            }

            // player -> finBox    -> finish
            // floor  -> finPlayer -> finBox
            if (f0 == player && f1 == finBox && f2 == finish)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer - 1][this->yPlayer] = finBox;
                return;
            }

            // finPlayer -> finBox    -> finish
            // finish    -> finPlayer -> finBox
            if (f0 == finPlayer && f1 == finBox && f2 == finish)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                this->map[this->xPlayer - 1][this->yPlayer] = finBox;
                return;
            }

            // player -> finish
            // floor  -> finPlayer
            if (f0 == player && f1 == finish)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = floor;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                return;
            }

            // finPlayer -> finish
            // finish    -> finPlayer
            if (f0 == finPlayer && f1 == finish)
            {
                this->xPlayer -= 1;

                this->map[this->xPlayer + 1][this->yPlayer] = finish;
                this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
                return;
            }
        }
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
            if (this->map[i][j] == finish)
            {
                path = ":/img/_pics/finish.png";
            }                
            else if (this->map[i][j] == floor)
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
            else if (this->map[i][j] == finPlayer)
            {
                path = ":/img/_pics/finPlayer.png";
            }
            else if (this->map[i][j] == box)
            {
                path = ":/img/_pics/box.png";
            }
            else if (this->map[i][j] == finBox)
            {
                path = ":/img/_pics/finBox.png";
            }

            QPixmap pixmap(path);
            painter->drawPixmap(x*i, y*j, x, y, pixmap);
        }
    }
}

void MainWindow::sayWon()
{
    for (int i = 0; i < this->length; i += 1)
    {
        for (int j = 0; j < this->length; j += 1)
        {
            if (this->map[i][j] == finish)
            {
                return;
            }
        }
    }

    this->close();

    QMessageBox msgBox;

    QString StrWinWidth = QString::number(this->WinWidth);
    msgBox.setStyleSheet("QLabel{min-width: " + StrWinWidth + "px; }");
    msgBox.setText("You won");
    msgBox.setWindowTitle("You won");

    msgBox.exec();
}
