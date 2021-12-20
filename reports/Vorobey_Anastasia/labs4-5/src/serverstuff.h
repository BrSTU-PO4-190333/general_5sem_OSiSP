#ifndef SERVERSTUFF_H
#define SERVERSTUFF_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>

class ServerStuff : public QObject
{
    Q_OBJECT

public:
    ServerStuff(QObject *pwgt);
    QTcpServer *tcpServer;
    QList<QTcpSocket *> getClients();
    bool isVacant();

public slots:
    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, const QString &str);
    qint64 sendFileToClient(QTcpSocket *socket, const QString &fileName);

signals:
    void gotNewMesssage(QString msg);
    void smbDisconnected();

private:
    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> clients;
    bool serverIsVacant;
};

#endif // SERVERSTUFF_H
