#ifndef GPI_GAMEWINDOW_HPP
#define GPI_GAMEWINDOW_HPP
#define LENGTH 15

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
#include <QIcon>
#include "gpi_MainWindow.hpp"

namespace Ui {
class gpi_GameWindow;
}

class gpi_GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gpi_GameWindow (QMainWindow *parent = nullptr);
    ~gpi_GameWindow ();

public slots:
    void gpi_gamewindow_animate();
    void gpi_on_actionRestartLevel_triggered();
    void gpi_on_actionMainMenu_triggered();

protected:
    void paintEvent (QPaintEvent *event) override;
    void keyPressEvent (QKeyEvent *e) override;

private:
    Ui::gpi_GameWindow *ui;

    const int   gpi_length              = LENGTH;
    const int   gpi_WinWidth            = 500;
    const int   gpi_WinHeight           = 500;
    int         gpi_xPlayer;
    int         gpi_yPlayer;
    // = = = = = = = = = = = = = = = =

    enum gpi_MapChar {
        err,
        wall,
        floor,
        player,
        finPlayer,
        box,
        finBox,
        finish,
    } gpi_map[LENGTH][LENGTH] = {{err}};

    void gpi_drawAxes (QPainter* painter);
    void gpi_drawTextures (QPainter *gpi_painter);
    void gpi_generateLevel1 ();
    void gpi_goBottom ();
    void gpi_goLeft ();
    void gpi_goRight ();
    void gpi_goTop ();
    void gpi_sayWon ();
};

#endif // GPI_GAMEWINDOW_HPP
