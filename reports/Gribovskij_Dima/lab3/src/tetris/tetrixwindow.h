#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QWidget>
#include <QuiLib/include/helper.h>
QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TetrixBoard;

//! [0]
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
            QPushButton *startButton;
            QPushButton *fontButton;
            QPushButton *quitButton;
            QPushButton *pauseButton;
            QPushButton *aboutButton;
        };
//! [0]

#endif
