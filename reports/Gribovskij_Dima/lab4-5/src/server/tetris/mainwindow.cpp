 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_stopServer->setVisible(false);
    ui->pushButton_update->setVisible(false);

    this->server = new ServerStuff(this);
    connect(this->server, &ServerStuff::gotNewMesssage,
            this, &MainWindow::gotNewMesssage);
    connect(this->server->tcpServer, &QTcpServer::newConnection,
            this, &MainWindow::smbConnectedToServer);
    connect(this->server, &ServerStuff::smbDisconnected,
            this, &MainWindow::smbDisconnectedFromServer);

    this->fileServer = new ServerStuff(this);

    this->setVersion(this->getDefaultVersion());
}

MainWindow::~MainWindow()
{
    delete server;
    delete ui;
}

void MainWindow::on_pushButton_startServer_clicked()
{
    ui->pushButton_stopServer->setVisible(true);
    ui->pushButton_update->setVisible(true);
    ui->pushButton_startServer->setVisible(false);
    if (!server->tcpServer->listen(QHostAddress::Any, 6547))
    {
        ui->textEdit_log->append(tr("<font color=\"red\"><b>Error!</b> The port is taken by some other service.</font>"));
        return;
    }
    connect(server->tcpServer, &QTcpServer::newConnection, server, &ServerStuff::newConnection);
    if (!fileServer->tcpServer->listen(QHostAddress::Any, 6788))
    {
        ui->textEdit_log->append(tr("<font color=\"red\"><b>Error!</b> The port is taken by some other service.</font>"));
        return;
    }
    connect(fileServer->tcpServer, &QTcpServer::newConnection, fileServer, &ServerStuff::newConnection);
    ui->textEdit_log->append(tr("<font color=\"green\"><b>Server started</b>, port is openned.</font>"));
}

void MainWindow::on_pushButton_stopServer_clicked()
{
    if(server->tcpServer->isListening())
    {
        ui->pushButton_update->setVisible(false);
        ui->pushButton_stopServer->setVisible(false);
        ui->pushButton_startServer->setVisible(true);

        disconnect(server->tcpServer, &QTcpServer::newConnection, server, &ServerStuff::newConnection);

        QList<QTcpSocket *> clients = server->getClients();
        for(int i = 0; i < clients.count(); i++)
        {
            server->sendToClient(clients.at(i), "0");
        }

        server->tcpServer->close();
        ui->textEdit_log->append(tr("<b>Server stopped</b>, post is closed"));
    }
    else
    {
        ui->textEdit_log->append(tr("<b>Error!</b> Server was not running"));
    }
}

void MainWindow::on_pushButton_testConn_clicked()
{
    if(server->tcpServer->isListening())
    {
        ui->textEdit_log->append(
                    QString("%1 %2")
                    .arg("Server is listening, number of connected clients:")
                    .arg(QString::number(server->getClients().count()))
                    );
    }
    else
    {
        ui->textEdit_log->append(
                    QString("%1 %2")
                    .arg("Server is not listening, number of connected clients:")
                    .arg(QString::number(server->getClients().count()))
                    );
    }
}

void MainWindow::smbConnectedToServer()
{
    ui->textEdit_log->append(tr("Somebody has connected"));
}

void MainWindow::smbDisconnectedFromServer()
{
    ui->textEdit_log->append(tr("Somebody has disconnected"));
}

void MainWindow::gotNewMesssage(QString msg)
{
    ui->textEdit_log->append(QString("New message: %1").arg(msg));
    if (msg.contains("version:"))
    {
        QList<QTcpSocket *> clients = server->getClients();
        this->server->sendToClient(clients.at(0), "version:" + this->mVersion);
    }
    else if (msg == "OK ON UPDATE")
    {
        //send update
        //ui->textEdit_log->append(QString("file:" + QApplication::applicationDirPath() + "/helper_class.dll"));
        QList<QTcpSocket *> clients = server->getClients();
        this->server->sendToClient(clients.at(0), "file:" + QApplication::applicationDirPath() + "/helper_class.dll");
    }
}

QString MainWindow::getDefaultVersion()
{
    QString val;
    QFile file;
    file.setFileName("server.json");
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

void MainWindow::setVersion(QString version)
{
    QJsonObject recordObject;
    recordObject.insert("version", QJsonValue::fromVariant(version));
    QJsonDocument doc(recordObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    QFile file;
    file.setFileName("server.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream( &file );
    stream << jsonString;
    file.close();

    this->mVersion = version;
}

QString MainWindow::getVersion()
{
    return this->mVersion;
}

void MainWindow::on_pushButton_update_clicked()
{
    this->setVersion(QString::number((this->getVersion()).toInt() + 1));

    if(server->tcpServer->isListening())
    {
        QList<QTcpSocket *> clients = server->getClients();
        for(int i = 0; i < clients.count(); i++)
        {
            server->sendToClient(clients.at(i), "version:" + this->mVersion);
        }
    }
}
