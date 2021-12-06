#include "tetrixboard.h"

#include <QApplication>
#include <QKeyEvent>
#include <QSettings>
#include <QFontDialog>
#include <QLabel>
#include <QPainter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>

TetrixBoard::TetrixBoard(QWidget *parent)
: QFrame(parent), isStarted(false), isPaused(false)
{
    mClient = new ClientStuff("localhost", 6547, 6788);
    bar = new QProgressBar();

    connect(this->mClient, &ClientStuff::hasReadSome, this, &TetrixBoard::receivedSomething);

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    clearBoard();

    this->mTimerUpdates = new QTimer(this);
    connect(this->mTimerUpdates, SIGNAL(timeout()), this, SLOT(handlePushCheckUpdateButton()));
    this->mTimerUpdates->start(10000);

    this->mTimerBar = new QTimer();
    setVersion(getDefaultVersion());
    connect(this->mTimerBar, SIGNAL(timeout()), this, SLOT(on_progressBar_valueChanged()));

    nextPiece.setRandomShape();
}

QSize TetrixBoard::sizeHint() const
{
    return QSize(BoardWidth * 15 + frameWidth() * 2,
                 BoardHeight * 15 + frameWidth() * 2);
}

QSize TetrixBoard::minimumSizeHint() const
{
    return QSize(BoardWidth * 5 + frameWidth() * 2,
                 BoardHeight * 5 + frameWidth() * 2);
}

void TetrixBoard::checkVersion()
{
    QString version = QString("Version: %1").arg(mVersion);
    QMessageBox::information(this, tr("Info"), version);
}

void TetrixBoard::download()
{
    QFile::rename("D:\\100\\client\\tetris\\tetrixpiece.cpp", "D:\\100\\client\\tetris\\tetrixpiece.cpp.bak");
    QFile::rename("D:\\100\\client\\tetris\\tetrixpiece.h", "D:\\100\\client\\tetris\\tetrixpiece.h.bak");

    QFile::copy("D:\\100\\server\\update\\helper_class.cpp", "D:\\100\\client\\tetris\\tetrixpiece.cpp");
    QFile::copy("D:\\100\\server\\update\\helper_class.h", "D:\\100\\client\\tetris\\tetrixpiece.h");
}

void TetrixBoard::receivedSomething(QString msg)
{
    if(msg.contains("version:"))
    {
        QString version = msg.remove(0, 8);

        QMessageBox msgBox;
        if(version == this->mVersion)
        {
            msgBox.setText("No available updates");
            msgBox.exec();
        }
        else
        {
            msgBox.setText("New version " + version + " is available");
            msgBox.setInformativeText("Do you want to update app?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int res = msgBox.exec();

            if (res == QMessageBox::Yes)
            {
                this->setVersion(version);
                QByteArray arrBlock;
                QDataStream out(&arrBlock, QIODevice::WriteOnly);
                QString answer = "OK ON UPDATE";
                out << quint16(0) << answer;

                download();

                out.device()->seek(0);
                out << quint16(arrBlock.size() - sizeof(quint16));

                this->mClient->tcpSocket->write(arrBlock);
            }
        }
    }
    if(msg.contains("file:"))
    {
        download();

        for(int i = 0; i < 100; ++i)
        {
            this->mTimerBar->start(500);
        }
    }
}


QString TetrixBoard::getDefaultVersion()
{
    QString val;
    QFile file;
    file.setFileName("client.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QString version = "1";
    if (val != "") {
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject json = doc.object();
        version = json["version"].toString();
    }

    return version;
}

void TetrixBoard::setVersion(QString version)
{
    QJsonObject recordObject;
    recordObject.insert("version", QJsonValue::fromVariant(version));
    QJsonDocument doc(recordObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    QFile file;
    file.setFileName("client.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream( &file );
    stream << jsonString;
    file.close();

    mVersion = version;
}

QString TetrixBoard::getVersion()
{
    return mVersion;
}

void TetrixBoard::start()
{
    if (isPaused)
        return;

    isStarted = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    score = 0;
    clearBoard();

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);

    newPiece();
    timer.start(timeoutTime(), this);
}

void TetrixBoard::changeFont() {
    bool Changed;
    QFont newFont = QFontDialog::getFont(&Changed);
    if (Changed) {
        QApplication::setFont(newFont);
        QSettings settings(this);
        settings.setValue("VIEWF", newFont);
    }
}

void TetrixBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
}

void TetrixBoard::About() {
    about();
}

void TetrixBoard::handlePushConnectButton()
{
    mClient->connect2host();
}

void TetrixBoard::handlePushCheckUpdateButton()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << "version:" + this->mVersion;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    mClient->tcpSocket->write(arrBlock);

//    updateHandler();
}

void TetrixBoard::handlePushDisconnectButton()
{
    mClient->closeConnection();
}

void TetrixBoard::on_progressBar_valueChanged()
{
    bar->setValue(bar->value() + 10);
}

void TetrixBoard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();

    if (isPaused) {
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
        return;
    }

    int boardTop = rect.bottom() - BoardHeight*squareHeight();

    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
            if (shape != NoShape)
                drawSquare(painter, rect.left() + j * squareWidth(),
                           boardTop + i * squareHeight(), shape);
        }
    }

    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(),
                       boardTop + (BoardHeight - y - 1) * squareHeight(),
                       curPiece.shape());
        }
    }
}

void TetrixBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
        case Qt::Key_Left:
            tryMove(curPiece, curX - 1, curY);
            break;
            case Qt::Key_Right:
                tryMove(curPiece, curX + 1, curY);
                break;
                case Qt::Key_Down:
                    tryMove(curPiece.rotatedRight(), curX, curY);
                    break;
                    case Qt::Key_Up:
                        tryMove(curPiece.rotatedLeft(), curX, curY);
                        break;
                        case Qt::Key_Space:
                            dropDown();
                            break;
                            case Qt::Key_D:
                                oneLineDown();
                                break;
                                default:
                                    QFrame::keyPressEvent(event);
    }
}

void TetrixBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}

void TetrixBoard::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
}

void TetrixBoard::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped(0);
}

void TetrixBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        shapeAt(x, y) = curPiece.shape();
    }

    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
}

void TetrixBoard::updateHandler() {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    QString answer = "OK ON UPDATE";
    out << quint16(0) << answer;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    mClient->tcpSocket->write(arrBlock);
}

void TetrixBoard::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }
            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, BoardHeight - 1) = NoShape;
        }
    }

    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        update();
    }
}

void TetrixBoard::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + curPiece.minY();

    if (!tryMove(curPiece, curX, curY)) {
        curPiece.setShape(NoShape);
        timer.stop();
        isStarted = false;
    }
}

bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}

void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    static constexpr QRgb colorTable[8] = {
            0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
            0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.lighter());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.darker());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}
