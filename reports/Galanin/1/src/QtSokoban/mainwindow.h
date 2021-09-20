#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define LENGTH 15

#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QPixmap>

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
    void Make1Level();
    void keyPressEvent(QKeyEvent* e) override;
    void paintEvent(QPaintEvent* event) override;
    void drawAxes(QPainter* painter);
    void drawTextures(QPainter* painter);

private:
    Ui::MainWindow *ui;
    const int length = LENGTH;
    const int WinWidth = 500;
    const int WinHeight = 500;
    enum MapChar {
        err,
        floor,
        wall,
    } map[LENGTH][LENGTH];
};
#endif // MAINWINDOW_H
