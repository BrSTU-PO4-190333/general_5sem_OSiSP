#ifndef GPI_GAMEWINDOW_HPP
#define GPI_GAMEWINDOW_HPP
#define LENGTH 15

#include <QWidget>
#include <QPainter>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class gpi_GameWindow;
}

class gpi_GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit gpi_GameWindow (QWidget *parent = nullptr);
    ~gpi_GameWindow ();

public slots:
    void gpi_gamewindow_animate();

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
