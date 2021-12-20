#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QFile>
#include <QTimer>
#include "popup.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void accept(int index);
    void loadingDoings();

private slots:
    void on_calendarWidget_selectionChanged();
    void on_add_doFortable_clicked();
    void on_showCurrectDate_clicked();
    void on_table_toDo_clicked(const QModelIndex &index);
    void on_del_doFortable_clicked();
    void on_save_doFortable_clicked();
    void on_accept_clicked();
    void NoticeToday();
    void NoticeThreeDaysNext();
    void NoticeOneDayNext();

private:
    Ui::MainWindow *ui;
    int currectDo = 0;
    PopUp *popUp;
    QTimer *timer, *timerNextDay, *timerThreeNextDay;

    QDate DateNext, DateThreeNext;
    bool flag = false;
    QString noticeTextToday, noticeTextThreeDaysNext, noticeTextOneDayNext; // Текст уведомлений
    QStringList save; // Сохраняемый список
    QStringList currectList; // Текущий список
    QStringList listData; // Список дат
    QStringList listTask; // Список задач
    QStringList listAccept; // Список выполненных задач

    int row = -1;

};
#endif // MAINWINDOW_H
