#ifndef GPI_MAINWINDOW_HPP
#define GPI_MAINWINDOW_HPP

#include <QMainWindow>
#include <QFontDialog>
#include <QSettings>

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
    void gpi_on_actionLevel1_triggered ();
    void on_pushButton_ShowGameWindow_clicked ();
    void on_pushButton_CloseMainWindow_clicked ();
    void gpi_on_actionSelectFont_triggered ();

private:
    Ui::gpi_MainWindow *ui;
};
#endif // GPI_MAINWINDOW_HPP
