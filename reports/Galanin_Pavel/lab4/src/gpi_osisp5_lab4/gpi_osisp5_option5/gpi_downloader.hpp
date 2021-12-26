#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

signals:
    void downloader_onReady();

public slots:
    void getData_helper();     // Метод инициализации запроса на получение данных
    void onResult_helper(QNetworkReply *reply);    // Слот обработки ответа о полученных данных
    void getData_helper_class();     // Метод инициализации запроса на получение данных
    void onResult_helper_class(QNetworkReply *reply);    // Слот обработки ответа о полученных данных
    void getData_about();     // Метод инициализации запроса на получение данных
    void onResult_about(QNetworkReply *reply);    // Слот обработки ответа о полученных данных

private:
    QNetworkAccessManager *manager_helper; // менеджер сетевого доступа
    QNetworkAccessManager *manager_helper_class; // менеджер сетевого доступа
    QNetworkAccessManager *manager_about; // менеджер сетевого доступа
};

#endif // DOWNLOADER_H
