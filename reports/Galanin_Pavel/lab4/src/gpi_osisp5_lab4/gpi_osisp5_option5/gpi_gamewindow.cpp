#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

gpi_GameWindow::gpi_GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gpi_GameWindow)
{
QTimer* gpi_timer;
// = = = = = = = = = = = = = = = =
    ui->setupUi(this);

    // gpi_ Устанавливаю таймер
    gpi_timer = new QTimer(this);
    connect (gpi_timer, SIGNAL(timeout()), this, SLOT(gpi_animate()));
    gpi_timer->start(100);

    connect(ui->gpi_action_align, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_align_triggered()));
    connect(ui->gpi_action_1_lvl, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_1_lvl_triggered()));
    connect(ui->gpi_action_2_lvl, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_2_lvl_triggered()));
    connect(ui->gpi_action_3_lvl, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_3_lvl_triggered()));
    connect(ui->gpi_action_4_lvl, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_4_lvl_triggered()));
    connect(ui->gpi_action_restart, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_restart_triggered()));
    connect(ui->gpi_action_about, SIGNAL(triggered()), this, SLOT(gpi_on_gpi_action_about_triggered()));

    gpi_on_gpi_action_restart_triggered();
}

gpi_GameWindow::~gpi_GameWindow()
{
    delete ui;
}

// gpi_ Функция, которая возвращает текстовый 1-ый уровень
QStringList gpi_get_1_level()
{
QStringList gpi_str_map;
// = = = = = = = = = = = = = = = =
    gpi_str_map = {
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxx...xxxxxx",
        "xxxxf@b..xxxxxx",
        "xxxxxx.bfxxxxxx",
        "xxxxfxxb.xxxxxx",
        "xxxx.x.f.xxxxxx",
        "xxxxb.Bbbfxxxxx",
        "xxxx...f..xxxxx",
        "xxxxxxxxxxxxxxx",
        "xBxxxxxxxxxxxxx",
        "xBxxxxxxxxxxxxx",
        "xBxxxxxxxxxxxxx",
        "xBxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx"
    };
    return gpi_str_map;
}

// gpi_ Функция, которая возвращает текстовый 2-ой уровень
QStringList gpi_get_2_level()
{
QStringList gpi_str_map;
// = = = = = = = = = = = = = = = =
    gpi_str_map = {
        "xxxxxxx.xxxxxxxxxxxxxxxxxxxxxx",
        "xxxxxxx.xxxxxxxxxxxxxxxxxxxxxx",
        "xx...xx.xx..................xx",
        "xx....x.x...................xx",
        "xx..........bbbbbbbbbbb.....xx",
        "xxx........................xxx",
        "xxxx......................xxxx",
        ".......@..........b...........",
        "xxxx..............fff.....xxxx",
        "xxx....x..........fff......xxx",
        "xx................fff.......xx",
        "xx....x.x.........fff.......xx",
        "xx...xx.xx..................xx",
        "xxxxxxx.xxxxxxxxxxxxxxxxxxxxxx",
        "xxxxxxx.xxxxxxxxxxxxxxxxxxxxxx",
    };
    return gpi_str_map;
}

// gpi_ Функция, которая возвращает текстовый 3-ий уровень
QStringList gpi_get_3_level()
{
QStringList gpi_str_map;
// = = = = = = = = = = = = = = = =
    gpi_str_map = {
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxx...xxxxxx",
        "xxxxf@b..xxxxxx",
        "xxxxxx.bfxxxxxx",
        "xxxxfxxb.xxxxxx",
        "xxxx.x.f.xxxxxx",
        "xxxxb.Bbbfxxxxx",
        "xxxx...f..xxxxx",
        "xxxxxxxxxxxxxxx",
        "xBxBxBxxxxxxxxx",
        "xBxBxBxxxxxxxxx",
        "xBxBxBxxxxxxxxx",
        "xBxBxBxxxxxxxxx",
        "xxxxxxxxxxxxxxx"
    };
    return gpi_str_map;
}

// gpi_ Функция, которая возвращает текстовый 4-ый уровень
QStringList gpi_get_4_level()
{
QStringList gpi_str_map;
// = = = = = = = = = = = = = = = =
    gpi_str_map = {
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxx...xxxxxx",
        "xxxxf@b..xxxxxx",
        "xxxxxx.bfxxxxxx",
        "xxxxfxxb.xxxxxx",
        "xxxx.x.f.xxxxxx",
        "xxxxb.Bbbfxxxxx",
        "xxxx...f..xxxxx",
        "xxxxxxxxxxxxxxx",
        "xBxBxBxxxxxxxxx",
        "xBxBxBxxxxxxxxx",
        "xBxxBxxxxxxxxxx",
        "xBxxBxxxxxxxxxx",
        "xxxxxxxxxxxxxxx"
    };
    return gpi_str_map;
}

// gpi_ Функция, которая генерирует уровень
void gpi_GameWindow::gpi_generate(QStringList gpi_str_map)
{
int gpi_i;
int gpi_j;
int gpi_max_width;
// = = = = = = = = = = = = = = = = =

    // gpi_ Определяет высоту карты
    this->gpi_mapHeight = gpi_str_map.length();
    qDebug() << "gpi_mapHeight: " << this->gpi_mapHeight;

    // gpi_ Определяем ширину карты
    gpi_max_width = 0;
    for (gpi_i = 0; gpi_i < gpi_str_map.length(); ++gpi_i)
    {
        if (gpi_max_width < gpi_str_map[gpi_i].length())
        {
            gpi_max_width = gpi_str_map[gpi_i].length();
        }
    }
    this->gpi_mapWidth = gpi_max_width;
    qDebug() << "gpi_mapWidth: " << this->gpi_mapWidth;

    // gpi_ Заполняем карту
    for (gpi_i = 0; gpi_i < this->gpi_mapWidth; ++gpi_i)
    {
        QVector<gpi_fields> gpi_1d_arr;
        for (gpi_j = 0; gpi_j < this->gpi_mapHeight; ++gpi_j)
        {
            gpi_1d_arr.push_back(gpi_err);
        }

        this->gpi_map.push_back(gpi_1d_arr);
    }

    // gpi_ Проходимся по массиву строк
    for (gpi_i = 0; gpi_i < this->gpi_mapHeight; ++gpi_i)
    {
        // gpi_ Проходимся по строке
        for (gpi_j = 0; gpi_j < this->gpi_mapWidth; ++gpi_j)
        {
            // gpi_ Если это пол
            if (gpi_str_map[gpi_i][gpi_j] == '.')
            {
                this->gpi_map[gpi_j][gpi_i] = gpi_floor;
                continue;
            }

            // gpi_ Если это стена
            if (gpi_str_map[gpi_i][gpi_j] == 'x')
            {
                this->gpi_map[gpi_j][gpi_i] = gpi_wall;
                continue;
            }

            // gpi_ Если это игрок
            if (gpi_str_map[gpi_i][gpi_j] == '@')
            {
                this->gpi_map[gpi_j][gpi_i] = gpi_player;
                this->gpi_xPlayer = gpi_i;
                this->gpi_yPlayer = gpi_j;
                continue;
            }

            // gpi_ Если это финиш
            if (gpi_str_map[gpi_i][gpi_j] == 'f')
            {
                this->gpi_map[gpi_j][gpi_i] = gpi_finish;
                continue;
            }

            // gpi_ Если это игрок на финише
            if (gpi_str_map[gpi_i][gpi_j] == 'A')
            {
                this->gpi_map[gpi_j][gpi_i] = gpi_finPlayer;
                this->gpi_xPlayer = gpi_i;
                this->gpi_yPlayer = gpi_j;
                continue;
            }

            // gpi_ Если это коробка
            if (gpi_str_map[gpi_i][gpi_j] == 'b')
            {
                this->gpi_map[gpi_j][gpi_i] = gpi_box;
                continue;
            }

            // gpi_ Если это коробка на финише
            if (gpi_str_map[gpi_i][gpi_j] == 'B')
            {
                this->gpi_map[gpi_j][gpi_i] = gpi_finBox;
                continue;
            }
            //qDebug() << gpi_j << gpi_map[gpi_j];
        }
        qDebug() << gpi_i << gpi_str_map[gpi_i];

    }

    qDebug() << this->gpi_map;
}

// gpi_ Функция, которая перерисовывает окно
void gpi_GameWindow::gpi_animate()
{
    repaint();
}

// gpi_ Функция перерисовки окна
void gpi_GameWindow::paintEvent(QPaintEvent *event)
{
int gpi_i;
int gpi_j;
int gpi_xk;
int gpi_yk;
QString gpi_img_path;
// = = = = = = = = = = = = = = = = =
    // gpi_ Убираем предупреждение Qt о не использовании перемменной
    Q_UNUSED (event);

    QPainter gpi_painter(this);

    // gpi_ Определяем коэффициенты расшерения ячеек массива
    gpi_yk = this->height() / this->gpi_mapHeight;
    gpi_xk = this->width() / this->gpi_mapWidth;

    for (gpi_i = 0; gpi_i < this->gpi_mapWidth; ++ gpi_i)
    {
        for (gpi_j = 0; gpi_j < this->gpi_mapHeight; ++gpi_j)
        {
            gpi_img_path = get_image_path(this->gpi_map[gpi_i][gpi_j]);
            QPixmap gpi_pixmap(gpi_img_path);
            gpi_painter.drawPixmap(gpi_xk * gpi_i, gpi_yk * gpi_j, gpi_xk, gpi_yk, gpi_pixmap);
        }
    }
}

// gpi_ Функция для определение пути к картинке
QString get_image_path(gpi_fields gpi_f)
{
    // gpi_ Если это пол
    if (gpi_f == gpi_floor)
    {
        return ":/@/_assets/gpi_GameWindow__floor.png";
    }

    // gpi_ Если это стена
    if (gpi_f == gpi_wall)
    {
        return ":/@/_assets/gpi_GameWindow__wall.png";
    }

    // gpi_ Если это игрок
    if (gpi_f == gpi_player)
    {
        return ":/@/_assets/gpi_GameWindow__player.png";
    }

    // gpi_ Если это финиш
    if (gpi_f == gpi_finish)
    {
        return ":/@/_assets/gpi_GameWindow__finish.png";
    }

    // gpi_ Если это игрок на финише
    if (gpi_f == gpi_finPlayer)
    {
        return ":/@/_assets/gpi_GameWindow__finPlayer.png";
    }

    // gpi_ Если это коробка
    if (gpi_f == gpi_box)
    {
        return ":/@/_assets/gpi_GameWindow__box.png";
    }

    // gpi_ Если это коробка на финише
    if (gpi_f == gpi_finBox)
    {
        return ":/@/_assets/gpi_GameWindow__finBox.png";
    }

    return ":/@/_assets/gpi_GameWindow__err.png";
}

// gpi_ Функция для выравнивания окна
void gpi_GameWindow::gpi_on_gpi_action_align_triggered()
{
    this->resize(this->gpi_mapWidth * 32, this->gpi_mapHeight * 32);
}

// gpi_ Функция заполняет массив 1-ым уровнем
void gpi_GameWindow::gpi_on_gpi_action_1_lvl_triggered()
{
    this->gpi_lvl = 1;
    gpi_on_gpi_action_restart_triggered();
}

// gpi_ Функция заполняет массив 2-ым уровнем
void gpi_GameWindow::gpi_on_gpi_action_2_lvl_triggered()
{
    this->gpi_lvl = 2;
    gpi_on_gpi_action_restart_triggered();
}

// gpi_ Функция заполняет массив 3-им уровнем
void gpi_GameWindow::gpi_on_gpi_action_3_lvl_triggered()
{
    this->gpi_lvl = 3;
    gpi_on_gpi_action_restart_triggered();
}

// gpi_ Функция заполняет массив 4-ым уровнем
void gpi_GameWindow::gpi_on_gpi_action_4_lvl_triggered()
{
    this->gpi_lvl = 4;
    gpi_on_gpi_action_restart_triggered();
}

// gpi_ Функция, которая отслеживает нажатие клавиш
void gpi_GameWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Up || e->key() == Qt::Key_W)
    {
        qDebug() << "up";
        gpi_goTop(
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer],
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer - 1],
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer - 2],
            this->gpi_yPlayer
        );
        return;
    }

    if (e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
    {
        qDebug() << "right";
        gpi_goRight(
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer],
            this->gpi_map[this->gpi_xPlayer + 1][this->gpi_yPlayer],
            this->gpi_map[this->gpi_xPlayer + 2][this->gpi_yPlayer],
            this->gpi_xPlayer,
            this->gpi_mapWidth
        );
        return;
    }

    if (e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
    {
        qDebug() << "down";
        gpi_goBottom(
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer],
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer + 1],
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer + 2],
            this->gpi_yPlayer,
            this->gpi_mapHeight
        );
        return;
    }

    if (e->key() == Qt::Key_Left || e->key() == Qt::Key_A)
    {
        qDebug() << "left";
        gpi_goLeft(
            this->gpi_map[this->gpi_xPlayer][this->gpi_yPlayer],
            this->gpi_map[this->gpi_xPlayer - 1][this->gpi_yPlayer],
            this->gpi_map[this->gpi_xPlayer - 2][this->gpi_yPlayer],
            this->gpi_xPlayer
        );
        return;
    }
}

void gpi_goTop(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_py)
{
    if (gpi_py == 2)
    {
        return;
    }

    // Было: player > floor > ...
    // Стало: floor > player > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_floor)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        return;
    }

    // Было: finPlayer > floor > ...
    // Стало: finish > player > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_floor)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        return;
    }

    // Было: player > finish > ...
    // Стало: floor > finPlayer > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finish)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        return;
    }

    // Было: finPlayer > finish > ...
    // Стало: finish > finPlayer > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finish)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        return;
    }

    // Было: player > box > floor
    // Стало: floor > player > box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: finPlayer > box > floor
    // Стало: finish > player > box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: player > box > finish
    // Стало: floor > player > finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: finPlayer > box > finish
    // Стало: finish > player > finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: player > finBox > floor
    // Стало: floor > finPlayer > box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: finPlayer > finBox > floor
    // Стало: finish > finPlayer > box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: player > finBox > finish
    // Стало: floor > finPlayer > finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: finPlayer > finBox > finish
    // Стало: finish > finPlayer > finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_py -= 1;
        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }
}

void gpi_goBottom(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_py, int gpi_max_y)
{
    if (gpi_py >= gpi_max_y - 1)
    {
        return;
    }

    // Было: gpi_player > gpi_floor > ...
    // Стало: gpi_floor > gpi_player > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_floor)
    {
        gpi_py += 1;

        gpi_f0 = gpi_floor;
        gpi_f1= gpi_player;
        return;
    }

    // Было: gpi_finPlayer > gpi_floor > ...
    // Стало: gpi_finish > gpi_player > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_floor)
    {
        gpi_py += 1;

        gpi_f0 = gpi_finish;
        gpi_f1= gpi_player;
        return;
    }

    // Было: gpi_player > gpi_finish > ...
    // Стало: gpi_floor > gpi_finPlayer > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finish)
    {
        gpi_py += 1;
        gpi_f0 = gpi_floor;
        gpi_f1= gpi_finPlayer;
        return;
    }

    // Было: gpi_finPlayer > gpi_finish > ...
    // Стало: gpi_finish > gpi_finPlayer > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finish)
    {
        gpi_py += 1;
        gpi_f0 = gpi_finish;
        gpi_f1= gpi_finPlayer;
        return;
    }

    // Было: gpi_player > gpi_box > gpi_floor
    // Стало: gpi_floor > gpi_player > gpi_box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_py += 1;

        gpi_f0 = gpi_floor;
        gpi_f1= gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_finPlayer > gpi_box > gpi_floor
    // Стало: gpi_finish > gpi_player > gpi_box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_py += 1;

        gpi_f0 = gpi_finish;
        gpi_f1= gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_player > gpi_finBox > gpi_floor
    // Стало: gpi_floor > gpi_finPlayer > gpi_box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_py += 1;

        gpi_f0 = gpi_floor;
        gpi_f1= gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_finPlayer > gpi_finBox > gpi_floor
    // Стало: gpi_finish > gpi_finPlayer > gpi_box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_py += 1;
        gpi_f0 = gpi_finish;
        gpi_f1= gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_player > gpi_box > gpi_finish
    // Стало: gpi_floor > gpi_player > gpi_finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_py += 1;
        gpi_f0 = gpi_floor;
        gpi_f1= gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_finPlayer > gpi_box > gpi_finish
    // Стало: gpi_finish > gpi_player > gpi_finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_py += 1;
        gpi_f0 = gpi_finish;
        gpi_f1= gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_player > gpi_finBox > gpi_finish
    // Стало: gpi_floor > gpi_finPlayer > gpi_finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_py += 1;
        gpi_f0 = gpi_floor;
        gpi_f1= gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_finPlayer > gpi_finBox > gpi_finish
    // Стало: gpi_finish > gpi_finPlayer > gpi_finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_py += 1;
        gpi_f0 = gpi_finish;
        gpi_f1= gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }
}

void gpi_goRight(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_px, int gpi_max_x)
{
    if (gpi_px >= gpi_max_x - 1)
    {
        return;
    }

    // Было: gpi_player > gpi_floor > ...
    // Стало: gpi_floor > gpi_player > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_floor)
    {
        gpi_px += 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        return;
    }

    // Было: gpi_finPlayer > gpi_floor > ...
    // Стало: gpi_finish > gpi_player > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_floor)
    {
        gpi_px += 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        return;
    }

    // Было: gpi_player > gpi_finish > ...
    // Стало: gpi_floor > gpi_finPlayer > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finish)
    {
        gpi_px += 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        return;
    }

    // Было: gpi_finPlayer > gpi_finish > ...
    // Стало: gpi_finish > gpi_finPlayer > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finish)
    {
        gpi_px += 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        return;
    }

    // Было: gpi_player > gpi_box > gpi_floor
    // Стало: gpi_floor > gpi_player > gpi_box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_px += 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_finPlayer > gpi_box > gpi_floor
    // Стало: gpi_finish > gpi_player > gpi_box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_px += 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_finPlayer > gpi_finBox > gpi_floor
    // Стало: gpi_finish > gpi_finPlayer > gpi_box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_px += 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_player > gpi_finBox > gpi_floor
    // Стало: gpi_floor > gpi_finPlayer > gpi_box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_px += 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_player > gpi_box > gpi_finish
    // Стало: gpi_floor > gpi_player > gpi_finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_px += 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_finPlayer > gpi_box > gpi_finish
    // Стало: gpi_finish > gpi_player > gpi_finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_px += 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_player > gpi_finBox > gpi_finish
    // Стало: gpi_floor > gpi_finPlayer > gpi_finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_px += 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_finPlayer > gpi_finBox > gpi_finish
    // Стало: gpi_finish > gpi_finPlayer > gpi_finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_px += 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }
}

void gpi_goLeft(gpi_fields& gpi_f0, gpi_fields& gpi_f1, gpi_fields& gpi_f2, int& gpi_px)
{
    if (gpi_px - 2 <= 0)
    {
        return;
    }

    // Было: gpi_player > gpi_floor > ...
    // Стало: gpi_floor > gpi_player > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_floor)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        return;
    }

    // Было: gpi_finPlayer > gpi_floor > ...
    // Стало: gpi_finish > gpi_player > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_floor)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        return;
    }

    // Было: gpi_player > gpi_finish > ...
    // Стало: gpi_floor > gpi_finPlayer > ...
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finish)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        return;
    }

    // Было: gpi_finPlayer > gpi_finish > ...
    // Стало: gpi_finish > gpi_finPlayer > ...
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finish)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        return;
    }

    // Было: gpi_player > gpi_box > gpi_floor
    // Стало: gpi_floor > gpi_player > gpi_box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_finPlayer > gpi_box > gpi_floor
    // Стало: gpi_finish > gpi_player > gpi_box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_floor)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_player > gpi_finBox > gpi_floor
    // Стало: gpi_floor > gpi_finPlayer > gpi_box
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_finPlayer > gpi_finBox > gpi_floor
    // Стало: gpi_finish > gpi_finPlayer > gpi_box
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_floor)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_box;
        return;
    }

    // Было: gpi_player > gpi_box > gpi_finish
    // Стало: gpi_floor > gpi_player > gpi_finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_finPlayer > gpi_box > gpi_finish
    // Стало: gpi_finish > gpi_player > gpi_finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_box && gpi_f2 == gpi_finish)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_player;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_player > gpi_finBox > gpi_finish
    // Стало: gpi_floor > gpi_finPlayer > gpi_finBox
    if (gpi_f0 == gpi_player && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_floor;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }

    // Было: gpi_finPlayer > gpi_finBox > gpi_finish
    // Стало: gpi_finish > gpi_finPlayer > gpi_finBox
    if (gpi_f0 == gpi_finPlayer && gpi_f1 == gpi_finBox && gpi_f2 == gpi_finish)
    {
        gpi_px -= 1;

        gpi_f0 = gpi_finish;
        gpi_f1 = gpi_finPlayer;
        gpi_f2 = gpi_finBox;
        return;
    }
}
