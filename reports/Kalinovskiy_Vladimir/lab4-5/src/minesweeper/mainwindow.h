#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QMap>
#include <QMessageBox>
#include "MyHeader.h"
#include "clientstuff.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer *mTimerBar;
    QTimer *mTimerUpdates;
    ClientStuff *mClient;
    QString mVersion;

    void setVersion(QString version);
    void download();
    QString getVersion();
    QString getDefaultVersion();
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QHBoxLayout* firstLayout;
    QGridLayout* gameLayout;
    QVBoxLayout* mainLayout;
    QComboBox* difficulties;
    QFont font;
    MyButton*** buttons;
    QPushButton* resetButton;
    QPushButton* showHighscores;
    QString** buttonText;
    QLabel* flags;
    QLabel* timeLabel;
    QTimer* timer;
    double time;
    int difficulty;
    int buttonRows, buttonColumns;
    int numberOfBombs;
    int disabledButtons;
    int numberOfFlags;
    bool endOfGame;
    QMap <double, QString> highscoresEasy;
    QMap <double, QString> highscoresMedium;
    QMap <double, QString> highscoresHard;
    QMessageBox* top10;

    void clearButtons();
    void setButtons(int n, int m, int size);
    void setBombs();
    void setNumbers();
    void onFreeButtonClicked(int i, int j);
    void bombClicked();
    void win();
    void reset();
    void showTop10(int difficulty);
    QComboBox* createComboBox();


private slots:
     void difficultyChanged();
     void buttonClicked();
     void rightButtonClicked();
     void tick();

public slots:
     void on_CheckUpdateButton_triggered();
     void on_ConnectButton_triggered();
     void on_DisconnectButton_triggered();
     void on_Version_triggered();

     void receivedSomething(QString msg);
};
#endif // MAINWINDOW_H
