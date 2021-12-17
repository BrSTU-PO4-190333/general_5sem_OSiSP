#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include <QBasicTimer>
#include <QFrame>
#include "clientstuff.h"
#include <QPointer>
#include <QProgressBar>
#include <QStatusBar>
#include <QTimer>
#include "tetrixpiece.h"
#include <QuiLib/include/about.h>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class TetrixBoard : public QFrame
        {
    Q_OBJECT

        public:
            TetrixBoard(QWidget *parent = nullptr);
            void changeFont();
            void setNextPieceLabel(QLabel *label);
            QSize sizeHint() const override;
            QSize minimumSizeHint() const override;

            QTimer *mTimerBar;
            QTimer *mTimerUpdates;
            ClientStuff *mClient;
            QString mVersion;

            QProgressBar *bar;

            void setVersion(QString version);
            void download();
            QString getVersion();
            QString getDefaultVersion();

    public slots:
            void start();
            void pause();
            void About();
            void handlePushCheckUpdateButton();
            void handlePushConnectButton();
            void handlePushDisconnectButton();
            void on_progressBar_valueChanged();
            void checkVersion();
            void receivedSomething(QString msg);
            void updateHandler();

            signals:
            void scoreChanged(int score);
            void linesRemovedChanged(int numLines);

        protected:
            void paintEvent(QPaintEvent *event) override;
            void keyPressEvent(QKeyEvent *event) override;
            void timerEvent(QTimerEvent *event) override;

        private:
            enum { BoardWidth = 10, BoardHeight = 22 };

            TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
            int timeoutTime() { return 1000 / (1 + 1); }
            int squareWidth() { return contentsRect().width() / BoardWidth; }
            int squareHeight() { return contentsRect().height() / BoardHeight; }
            void clearBoard();
            void dropDown();
            void oneLineDown();
            void pieceDropped(int dropHeight);
            void removeFullLines();
            void newPiece();
            bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
            void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);

            QBasicTimer timer;
            bool isStarted;
            bool isPaused;
            bool isWaitingAfterLine;
            TetrixPiece curPiece;
            TetrixPiece nextPiece;
            int curX;
            int curY;
            int numLinesRemoved;
            int score;
            TetrixShape board[BoardWidth * BoardHeight];

        };

#endif
