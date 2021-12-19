#include "startwindow.h"


StartWindow::StartWindow(QWidget *parent) : QDialog(parent, Qt::WindowCloseButtonHint)
{
    this->setStyleSheet(
                " QDialog {                      "
                "    background-color: Lavender; "
                " }                              "
                "                                "
                " QRadioButton {                 "
                "    font-size: 15px;            "
                " }                              "
                "                                "
                " QPushButton {                  "
                "    font-size: 20px;            "
                " }                              "
                       );

    newg =   new QRadioButton(GetStart());
    start =  new QPushButton (Start());
    start->setEnabled(false);
    exit =  new  QPushButton (Exit());

    startgame = new QVBoxLayout;
    startgame->addWidget(newg  );


    buttons = new QHBoxLayout;
    buttons->addWidget(start);
    buttons->addWidget(exit );

    full = new QVBoxLayout;
    full->addLayout(startgame);
    full->addLayout(buttons);

    setLayout(full);

    windowIcon = QIcon(":/image/bomb.png");
    this->setWindowIcon(windowIcon);

    connect(newg,   &QRadioButton::clicked, this, &StartWindow::unlockingButton);

    connect(start,  &QPushButton ::clicked, this, &StartWindow::clicked_start  );
    connect(exit,   &QPushButton ::clicked, this, &StartWindow::clicked_exit   );
}

StartWindow::~StartWindow()
{
}

void StartWindow::unlockingButton()
{
    start->setEnabled(true);
}

int StartWindow::clicked_start()
{
    this->close();
    int complexity = newg->isChecked();
    return complexity;
}

bool StartWindow::clicked_exit()
{
    std::exit(1);
}
