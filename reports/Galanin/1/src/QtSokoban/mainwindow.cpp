#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->label = new QLabel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up || e->key() == Qt::Key_W) {
        this->label->setText("up");
    }
    else if(e->key() == Qt::Key_Right || e->key() == Qt::Key_D) {
        this->label->setText("right");
    }
    else if(e->key() == Qt::Key_Down || e->key() == Qt::Key_S) {
        this->label->setText("down");
    }
    else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_A) {
        this->label->setText("left");
    }
}
