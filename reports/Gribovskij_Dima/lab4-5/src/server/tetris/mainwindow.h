#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QThread>
#include "serverstuff.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setVersion(QString version);
    QString getVersion();
    QString getDefaultVersion();
    void sendFile();
private slots:
    void on_pushButton_stopServer_clicked();
    void on_pushButton_startServer_clicked();
    void on_pushButton_testConn_clicked();
    void smbConnectedToServer();
    void smbDisconnectedFromServer();
    void gotNewMesssage(QString msg);

    void on_pushButton_update_clicked();

private:
    Ui::MainWindow *ui;
    ServerStuff *server;
    ServerStuff *fileServer;
    QString mVersion;
};

#endif // MAINWINDOW_H
