/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QCalendarWidget *calendarWidget;
    QPushButton *showCurrectDate;
    QPushButton *add_doFortable;
    QTableWidget *table_toDo;
    QPushButton *del_doFortable;
    QPushButton *save_doFortable;
    QPushButton *accept;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        calendarWidget = new QCalendarWidget(centralwidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(11, 60, 321, 261));
        showCurrectDate = new QPushButton(centralwidget);
        showCurrectDate->setObjectName(QString::fromUtf8("showCurrectDate"));
        showCurrectDate->setGeometry(QRect(100, 20, 151, 31));
        add_doFortable = new QPushButton(centralwidget);
        add_doFortable->setObjectName(QString::fromUtf8("add_doFortable"));
        add_doFortable->setGeometry(QRect(370, 20, 81, 31));
        table_toDo = new QTableWidget(centralwidget);
        if (table_toDo->columnCount() < 1)
            table_toDo->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_toDo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        table_toDo->setObjectName(QString::fromUtf8("table_toDo"));
        table_toDo->setGeometry(QRect(360, 60, 401, 311));
        del_doFortable = new QPushButton(centralwidget);
        del_doFortable->setObjectName(QString::fromUtf8("del_doFortable"));
        del_doFortable->setGeometry(QRect(470, 20, 81, 31));
        save_doFortable = new QPushButton(centralwidget);
        save_doFortable->setObjectName(QString::fromUtf8("save_doFortable"));
        save_doFortable->setGeometry(QRect(360, 380, 101, 31));
        accept = new QPushButton(centralwidget);
        accept->setObjectName(QString::fromUtf8("accept"));
        accept->setGeometry(QRect(660, 380, 101, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        showCurrectDate->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\321\203\321\216 \320\264\320\260\321\202\321\203", nullptr));
        add_doFortable->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        del_doFortable->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        save_doFortable->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        accept->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
