#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define LENGTH 15

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* e) override;
    void paintEvent(QPaintEvent* event) override;
    void drawAxes(QPainter* painter);

private:
    Ui::MainWindow *ui;
    const int length = LENGTH;
    char map[LENGTH][LENGTH];
    const int WinWidth = 500;
    const int WinHeight = 500;
};
#endif // MAINWINDOW_H
