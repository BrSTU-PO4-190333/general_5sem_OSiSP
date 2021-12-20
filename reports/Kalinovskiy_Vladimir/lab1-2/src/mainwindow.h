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
#include <QString>
#include "MyHeader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
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
    QComboBox* temp;

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
private:
    Ui::MainWindow *ui;

private slots:
     void difficultyChanged();
     void buttonClicked();
     void rightButtonClicked();
     void tick();
     void on_actionAbout_triggered();
     void on_actionFont_triggered();
};
#endif // MAINWINDOW_H
