#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QProgressBar>
#include <QStatusBar>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QuiLib/include/helper.h>
QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TetrixBoard;

class TetrixWindow : public QWidget
        {
    Q_OBJECT

        public:
            TetrixWindow(QWidget *parent = nullptr);

        private:
            QLabel *createLabel(const QString &text);

            TetrixBoard *board;

            QLCDNumber *scoreLcd;
            QLCDNumber *fontLcd;
            QLCDNumber *linesLcd;
            QLCDNumber *aboutLcd;
            QLCDNumber *connectLcd;
            QLCDNumber *disconnectLcd;
            QLCDNumber *checkLcd;
            QLCDNumber *progressLcd;
            QLCDNumber *statusLcd;
            QLCDNumber *checkVersionLcd;
//            QLCDNumber *updateLcd;

            QPushButton *startButton;
//            QPushButton *updateButton;
            QPushButton *fontButton;
            QPushButton *quitButton;
            QPushButton *pauseButton;
            QPushButton *aboutButton;
            QPushButton *connectButton;
            QPushButton *disconnectButton;
            QPushButton *checkButton;
            QPushButton *checkVersionButton;

            QProgressBar *progressBar;
        };

#endif
