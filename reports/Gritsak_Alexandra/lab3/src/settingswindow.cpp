#include "settingswindow.h"
#include "game.h"

SettingsWindow::SettingsWindow(int &sizeField, int &countMines, QWidget *parent) : QDialog(parent, Qt::WindowCloseButtonHint)
{
    up_left = new QVBoxLayout;
    up_right = new QVBoxLayout;
    up = new QHBoxLayout;
    down = new QHBoxLayout;
    full = new QVBoxLayout;
    rb_easy = new QRadioButton("Easy");
    pb_ok = new QPushButton("&Ok");
    pb_cancel = new QPushButton("&Cancel");
    le_size = new QLineEdit;
    le_countOfMines = new QLineEdit;

    le_size->setStyleSheet(
                "QLineEdit {"
                "    width: 40px;"
                "}"
                           );
    le_countOfMines->setStyleSheet(
                "QLineEdit {"
                "    width: 40px;"
                "}"
                                   );


    up_left->addWidget(rb_easy);
    up->addLayout(up_left);
    up->addStretch(50);
    up->addLayout(up_right);
    down->addWidget(pb_ok);
    down->addWidget(pb_cancel);
    full->addLayout(up);
    full->addLayout(down);
    setLayout(full);

    if (sizeField == 10 && countMines == 8)
        rb_easy->setChecked(true);


    connect(pb_ok,     &QPushButton::clicked, this, &SettingsWindow::clicked_ok    );
    connect(pb_cancel, &QPushButton::clicked, this, &SettingsWindow::clicked_cancel);
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::clicked_cancel()
{
    this->close();
}

void SettingsWindow::clicked_ok()
{
    if (rb_easy->isChecked())
    {
        sizeField = 10;
        countMines = 8;
    }

    this->close();
}
