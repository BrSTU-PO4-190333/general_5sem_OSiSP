#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

gpi_GameWindow::gpi_GameWindow (QMainWindow *parent) :
    QMainWindow (parent),
    ui (new Ui::gpi_GameWindow)
{
    QTimer*         timer       = new QTimer (this);
    // = = = = = = = = = = = = = = = =

    ui->setupUi (this);
    this->setWindowIcon (QIcon (":/@gpi@/_assets/gpi_MainWindow__favicon.png"));

    connect(ui->actionRestartLevel, SIGNAL(triggered ()), this, SLOT(gpi_on_actionRestartLevel_triggered ()));
    connect(ui->actionMainMenu, SIGNAL(triggered ()), this, SLOT(gpi_on_actionMainMenu_triggered ()));

    connect (timer, SIGNAL (timeout ()), this, SLOT (gpi_gamewindow_animate ()));
    timer->start (100);

    this->setFixedSize (this->gpi_WinWidth, this->gpi_WinHeight);
    this->gpi_generateLevel1 ();
}

gpi_GameWindow::~gpi_GameWindow ()
{
    delete ui;
}

void gpi_GameWindow::paintEvent (QPaintEvent *event)
{
    QPainter        gpi_painter (this);
    // = = = = = = = = = = = = = = = =

    Q_UNUSED (event);
    this->gpi_sayWon ();
    this->gpi_drawAxes (&gpi_painter);
    this->gpi_drawTextures (&gpi_painter);
}

void gpi_GameWindow::gpi_gamewindow_animate ()
{
    repaint();
}

void gpi_GameWindow::gpi_on_actionRestartLevel_triggered ()
{
    this->gpi_generateLevel1 ();
}

void gpi_GameWindow::gpi_on_actionMainMenu_triggered ()
{
    gpi_MainWindow* gpi_mw = new gpi_MainWindow ();
    gpi_mw->show ();
    this->close ();
}

void gpi_GameWindow::keyPressEvent (QKeyEvent *e)
{
    switch(e->key ())
    {
        case Qt::Key_Up:
        case Qt::Key_W:
            this->gpi_goTop ();
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            this->gpi_goRight ();
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            this->gpi_goBottom ();
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            this->gpi_goLeft ();
            break;
    }
}
