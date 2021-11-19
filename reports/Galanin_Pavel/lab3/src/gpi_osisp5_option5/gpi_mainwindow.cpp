#include "gpi_mainwindow.hpp"
#include "ui_gpi_mainwindow.h"

gpi_MainWindow::gpi_MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::gpi_MainWindow)
{
    ui->setupUi (this);
    this->setWindowIcon (QIcon (":/@gpi@/_assets/gpi_MainWindow__favicon.png"));

    connect(ui->actionLevel1, SIGNAL(triggered()), this, SLOT(gpi_on_actionLevel1_triggered()));
    connect(ui->actionSelectFont, SIGNAL(triggered()), this, SLOT(gpi_on_actionSelectFont_triggered()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), this, SLOT(gpi_on_actionAboutQt_triggered()));
    connect(ui->actionAboutAuthor, SIGNAL(triggered()), this, SLOT(gpi_on_actionAboutAuthor_triggered()));
}

gpi_MainWindow::~gpi_MainWindow ()
{
    delete ui;
}

void gpi_MainWindow::gpi_on_actionLevel1_triggered ()
{
    gpi_GameWindow* gpi_gw = new gpi_GameWindow();
    gpi_gw->show ();
    this->close ();
}

void gpi_MainWindow::on_pushButton_ShowGameWindow_clicked ()
{
    gpi_GameWindow* gpi_gw = new gpi_GameWindow();
    gpi_gw->show ();
    this->close ();
}


void gpi_MainWindow::on_pushButton_CloseMainWindow_clicked ()
{
    this->close ();
}

void gpi_MainWindow::gpi_on_actionSelectFont_triggered ()
{
    bool ok;
    QFont gpi_newFont = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->centralwidget->setFont(gpi_newFont);
        QSettings settings(this);
        settings.setValue("gpi_VIEWF", gpi_newFont);
    }
}

void gpi_MainWindow::gpi_on_actionAboutQt_triggered ()
{
    qApp->aboutQt();
}

void gpi_MainWindow::gpi_on_actionAboutAuthor_triggered ()
{
    QString str = "\
Разработчик: \n \
    студент 3-его курса \n \
    V-го семестра \n \
    факультета ЭИС \n \
    группы ПО-4 (1) \n \
    Галанин П. И. \n \
    GitHub: Pavel-Innokentevich-Galanin \n \
    Email: po000406@g.bstu.by \n \
";
    QMessageBox::about(this, "О программе", str);
}
