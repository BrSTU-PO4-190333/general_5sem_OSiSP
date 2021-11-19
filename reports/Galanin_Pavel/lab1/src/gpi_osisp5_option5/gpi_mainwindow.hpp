#ifndef GPI_MAINWINDOW_HPP
#define GPI_MAINWINDOW_HPP

#include <QMainWindow>
#include "gpi_gamewindow.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class gpi_MainWindow; }
QT_END_NAMESPACE

class gpi_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    gpi_MainWindow (QWidget *parent = nullptr);
    ~gpi_MainWindow ();

private slots:
    void on_pushButton_ShowGameWindow_clicked ();
    void on_pushButton_CloseMainWindow_clicked ();

private:
    Ui::gpi_MainWindow *ui;
    gpi_GameWindow gpi_gw;
};
#endif // GPI_MAINWINDOW_HPP
