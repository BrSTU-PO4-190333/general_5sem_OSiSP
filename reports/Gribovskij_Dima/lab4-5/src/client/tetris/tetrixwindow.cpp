#include "tetrixboard.h"
#include "tetrixwindow.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QTextEdit>
#include <QDebug>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>

TetrixWindow::TetrixWindow(QWidget *parent)
: QWidget(parent), board(new TetrixBoard)
{

    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);

    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    aboutLcd = new QLCDNumber(5);
    aboutLcd->setSegmentStyle(QLCDNumber::Filled);

    fontLcd = new QLCDNumber(5);
    fontLcd->setSegmentStyle(QLCDNumber::Filled);

    connectLcd = new QLCDNumber(5);
    connectLcd->setSegmentStyle(QLCDNumber::Filled);

    disconnectLcd = new QLCDNumber(5);
    disconnectLcd->setSegmentStyle(QLCDNumber::Filled);

    checkLcd = new QLCDNumber(5);
    checkLcd->setSegmentStyle(QLCDNumber::Filled);

    progressLcd = new QLCDNumber(5);
    progressLcd->setSegmentStyle(QLCDNumber::Filled);

    statusLcd = new QLCDNumber(5);
    statusLcd->setSegmentStyle(QLCDNumber::Filled);

    checkVersionLcd = new QLCDNumber(5);
    checkVersionLcd->setSegmentStyle(QLCDNumber::Filled);

//    updateLcd = new QLCDNumber(5);
//    updateLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    aboutButton = new QPushButton(tr("&About"));
    fontButton = new QPushButton(tr("&Font"));
    connectButton = new QPushButton(tr("&Connect"));
    disconnectButton = new QPushButton(tr("&Disconnect"));
    checkButton = new QPushButton(tr("&Check Update"));
    checkVersionButton = new QPushButton(tr("&Check Version"));
//    updateButton = new QPushButton(tr("&Update"));

    pauseButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, board, &TetrixBoard::start);
    connect(quitButton , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(pauseButton, &QPushButton::clicked, board, &TetrixBoard::pause);
    connect(aboutButton, &QPushButton::clicked, board, &TetrixBoard::About);
    connect(fontButton, &QPushButton::clicked, board, &TetrixBoard::changeFont);
    connect(connectButton, &QPushButton::clicked, board, &TetrixBoard::handlePushConnectButton);
    connect(disconnectButton, &QPushButton::clicked, board, &TetrixBoard::handlePushDisconnectButton);
    connect(checkButton, &QPushButton::clicked, board, &TetrixBoard::handlePushCheckUpdateButton);
    connect(checkVersionButton, &QPushButton::clicked, board, &TetrixBoard::checkVersion);
//    connect(updateButton, &QPushButton::clicked, board, &TetrixBoard::updateHandler);
//    connect(updateButton, &QPushButton::clicked, board, &TetrixBoard::receivedSomething);
#if __cplusplus >= 201402L
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, QOverload<int>::of(&QLCDNumber::display));
#endif

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("")), 0, 0);
    layout->addWidget(createLabel(tr("")), 2, 0);
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(board, 0, 1, 6, 1);
    layout->addWidget(createLabel(tr("SCORE")), 0, 2);
    layout->addWidget(scoreLcd, 1, 2);
    layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 2);
    layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(quitButton, 4, 2);
    layout->addWidget(pauseButton, 5, 2);
    layout->addWidget(aboutButton, 6, 2);
    layout->addWidget(fontButton, 5, 0);
    layout->addWidget(connectButton, 1, 0);
    layout->addWidget(disconnectButton, 2, 0);
    layout->addWidget(checkButton, 3, 0);
//    layout->addWidget(updateButton, 7, 0);
    layout->addWidget(checkVersionButton, 8, 0);
    setLayout(layout);

    setWindowTitle(getWindowTitle());

    resize(550, 370);
}

QLabel *TetrixWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
