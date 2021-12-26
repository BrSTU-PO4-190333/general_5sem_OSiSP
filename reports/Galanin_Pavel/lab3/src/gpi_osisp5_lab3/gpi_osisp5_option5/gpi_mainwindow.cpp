#include "gpi_mainwindow.hpp"
#include "gpi_gamewindow.hpp"
#include "ui_gpi_mainwindow.h"

gpi_MainWindow::gpi_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gpi_MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon (QIcon (":/@/_assets/gpi_favicon.png"));

    QVariant gpi_variant = QSettings(this).value("gpi_VIEWF");
    QFont gpi_font = gpi_variant.value<QFont>();
    ui->centralwidget->setFont(gpi_font);

    connect(ui->gpi_action_about, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_about_triggered()));
    connect(ui->gpi_action_font, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_font_triggered()));
}

gpi_MainWindow::~gpi_MainWindow()
{
    delete ui;
}

// gpi_ Функция, которая открывает окно с игрой (GameWindow)
void gpi_MainWindow::on_gpi_pushButton_start_clicked()
{
gpi_GameWindow* gpi_gw;
// = = = = = = = = = = = = = = = =
    gpi_gw = new gpi_GameWindow(this);  // gpi_ Создаем объект окна
    gpi_gw->show();                     // gpi_ Делаем окно видимым
}

// gpi_ Функция, которая закрывает окно меню (MainWindow)
void gpi_MainWindow::on_gpi_pushButton_close_clicked()
{
    this->close();                      // gpi_ Закрытия окна
}
