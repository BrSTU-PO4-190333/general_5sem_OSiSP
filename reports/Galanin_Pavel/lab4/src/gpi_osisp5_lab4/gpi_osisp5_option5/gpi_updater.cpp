#include "gpi_mainwindow.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

void gpi_MainWindow::on_gpi_pushButton_update_clicked()
{
    qDebug() << "on_gpi_pushButton_update_clicked()";
    QMessageBox::information(this, "Процесс обновления", "Происходит запрос на сервер");
    networkManager = new QNetworkAccessManager();

    // Подключаем networkManager к обработчику ответа
    connect(networkManager, &QNetworkAccessManager::finished, this, &gpi_MainWindow::onResult);

    // Получаем данные, а именно JSON файл с сайта по определённому url
    networkManager->get(QNetworkRequest(QUrl("http://localhost:3002/versions")));
}

void gpi_MainWindow::onResult(QNetworkReply *reply)
{
QString client_helper;
QString client_helper_class;
QString client_about;

QString server_helper;
QString server_helper_class;
QString server_about;

QFile file;
QString file_inner;

QJsonDocument client_document;
QJsonObject client_json;

QJsonDocument server_document;
QJsonObject server_json;

QString gpi_str_verions;
// = = = = = = = = = = = = = = = =
    if (reply->error() != QNetworkReply::NoError)
    {
        QMessageBox::critical(this, "Проблема со сервером", "Ошибка подключения к серверу");
    }

    // Если ошибки отсутсвуют
    if(!reply->error())
    {
        QMessageBox::information(this, "Процесс обновления", "Происходит сверка версий");

        // = = = Работа с клиентом = = =

        file.setFileName(":/@/gpi_versions.json"); // Назначаем имя
        file.open(QIODevice::ReadOnly | QIODevice::Text); // Открываем файл
        file_inner = file.readAll(); // Читаем текст из файла
        file.close(); // Закрываем файл
        qDebug() << file_inner;

        client_document = QJsonDocument::fromJson(file_inner.toUtf8());
        client_json = client_document.object();

        client_helper = client_json["helper"].toString();
        client_helper_class = client_json["helper_class"].toString();
        client_about = client_json["about"].toString();

        // = = = Работа с сервером = = =

        // То создаём объект Json Document, считав в него все данные из ответа
        server_document = QJsonDocument::fromJson(reply->readAll());
        server_json = server_document.object();
        qDebug() << "document:" << server_document;
        qDebug() << "json:" << server_json;

        server_helper = server_json.value("helper").toString();
        server_helper_class = server_json.value("helper_class").toString();
        server_about = server_json.value("about").toString();

        // = = = Сравнение версий = = =

        gpi_str_verions
            = client_helper + " ~ " + server_helper + " - helper.dll \n"
            + client_helper_class + " ~ " + server_helper_class + " - helper_class.dll \n"
            + client_about + " ~ " + server_about  + " - about.dll \n";

        QMessageBox::information(this, "Процесс обновления", gpi_str_verions);

        if (client_helper.compare(server_helper)) {
            QMessageBox::information(this, "Процесс обновления", "Найдено обновление helper.dll");
            Downloader* dd = new Downloader();
            dd->getData_helper();
        }

        if (client_helper_class.compare(server_helper_class)) {
            QMessageBox::information(this, "Процесс обновления", "Найдено обновление helper_class.dll");
            Downloader* dd = new Downloader();
            dd->getData_helper_class();
        }

        if (client_about.compare(server_about)) {
            QMessageBox::information(this, "Процесс обновления", "Найдено обновление about.dll");
            Downloader* dd = new Downloader();
            dd->getData_about();
        }

        QString jsonString = server_document.toJson(QJsonDocument::Indented);
        qDebug() << "================================" << jsonString;
        QFile file_version;
        file_version.setFileName("gpi_versions.json");
        file_version.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream( &file_version );
        stream << jsonString;
        file_version.close();

    }
    reply->deleteLater();
}
