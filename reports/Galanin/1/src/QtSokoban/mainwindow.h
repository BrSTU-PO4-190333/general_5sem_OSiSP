#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define LENGTH 15

#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QPixmap>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void animate();

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
        wall,
        floor,
        player,
        box,
    } map[LENGTH][LENGTH];
    enum MapFinish {
        noFinish,
        finish,
    } finishMap[LENGTH][LENGTH];

    int xPlayer = 9;
    int yPlayer = 11;
};
#endif // MAINWINDOW_H
