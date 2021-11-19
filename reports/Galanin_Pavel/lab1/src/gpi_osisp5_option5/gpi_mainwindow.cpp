#include "gpi_mainwindow.hpp"
#include "ui_gpi_mainwindow.h"

gpi_MainWindow::gpi_MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::gpi_MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon (QIcon (":/@gpi@/_assets/gpi_MainWindow__favicon.png"));
}

gpi_MainWindow::~gpi_MainWindow ()
{
    delete ui;
}



void gpi_MainWindow::on_pushButton_ShowGameWindow_clicked ()
{
    gpi_gw.show ();
}


void gpi_MainWindow::on_pushButton_CloseMainWindow_clicked ()
{
    this->close ();
}

