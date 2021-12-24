#ifndef GPI_GAMEWINDOW_HPP
#define GPI_GAMEWINDOW_HPP

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QLibrary>
#include <QMessageBox>

namespace Ui {
class gpi_GameWindow;
}

enum gpi_fields{
    gpi_err,
    gpi_wall,
    gpi_floor,
    gpi_player,
    gpi_finPlayer,
    gpi_box,
    gpi_finBox,
    gpi_finish,
};

class gpi_GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gpi_GameWindow(QWidget *parent = nullptr);
    ~gpi_GameWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::gpi_GameWindow *ui;
    QVector <QVector<gpi_fields>> gpi_map;
    void gpi_generate(QStringList gpi_str_map);
    int gpi_xPlayer;
    int gpi_yPlayer;
    int gpi_mapHeight;
    int gpi_mapWidth;
    int gpi_lvl;

private slots:
    void gpi_animate();
    void gpi_on_gpi_action_align_triggered();
    void gpi_on_gpi_action_1_lvl_triggered();
    void gpi_on_gpi_action_2_lvl_triggered();
    void gpi_on_gpi_action_3_lvl_triggered();
    void gpi_on_gpi_action_4_lvl_triggered();
    void gpi_on_gpi_action_restart_triggered();
    void gpi_on_gpi_action_about_triggered();
};

QString get_image_path(gpi_fields gpi_f);
void gpi_goTop(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_py);
void gpi_goBottom(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_py, int gpi_max_y);
void gpi_goRight(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_px, int gpi_max_x);
void gpi_goLeft(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_px);

#endif // GPI_GAMEWINDOW_HPP
