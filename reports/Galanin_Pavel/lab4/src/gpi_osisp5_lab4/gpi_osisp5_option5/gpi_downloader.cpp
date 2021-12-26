#include "gpi_downloader.hpp"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    qDebug() << "Downloader";
    // Инициализируем менеджер ...
    manager_helper = new QNetworkAccessManager();
    manager_helper_class = new QNetworkAccessManager();
    manager_about = new QNetworkAccessManager();
    // ... и подключаем сигнал о завершении получения данных к обработчику полученного ответа
    connect(manager_helper, &QNetworkAccessManager::finished, this, &Downloader::onResult_helper);
    connect(manager_helper_class, &QNetworkAccessManager::finished, this, &Downloader::onResult_helper_class);
    connect(manager_about, &QNetworkAccessManager::finished, this, &Downloader::onResult_about);
}

void Downloader::getData_helper()
{
    qDebug() << "getData";
    QUrl url("http://localhost:3002/gpi_helper.dll"); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    manager_helper->get(request);      // Выполняем запрос
}

void Downloader::getData_helper_class()
{
    qDebug() << "getData";
    QUrl url("http://localhost:3002/gpi_helper_class.dll"); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    manager_helper_class->get(request);      // Выполняем запрос
}

void Downloader::getData_about()
{
    qDebug() << "getData";
    QUrl url("http://localhost:3002/gpi_about.dll"); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    manager_about->get(request);      // Выполняем запрос
}

void Downloader::onResult_helper(QNetworkReply *reply)
{
    qDebug() << "onResult";
    // Если в процесе получения данных произошла ошибка
    if(reply->error())
    {
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    }
    else
    {
        // В противном случае создаём объект для работы с файлом
        QFile *file = new QFile("./gpi_helper.dll");
        // Создаём файл или открываем его на перезапись ...
        if(file->open(QFile::WriteOnly))
        {
            qDebug() << "write helper.dll";
            file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
            file->close();                  // закрываем файл
            qDebug() << "Downloading is completed";
            emit downloader_onReady(); // Посылаем сигнал о завершении получения файла
        }
    }
}

void Downloader::onResult_helper_class(QNetworkReply *reply)
{
    qDebug() << "onResult";
    // Если в процесе получения данных произошла ошибка
    if(reply->error())
    {
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    }
    else
    {
        // В противном случае создаём объект для работы с файлом
        QFile *file = new QFile("./gpi_helper_class.dll");
        // Создаём файл или открываем его на перезапись ...
        if(file->open(QFile::WriteOnly))
        {
            qDebug() << "write helper_class.dll";
            file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
            file->close();                  // закрываем файл
            qDebug() << "Downloading is completed";
            emit downloader_onReady(); // Посылаем сигнал о завершении получения файла
        }
    }
}

void Downloader::onResult_about(QNetworkReply *reply)
{
    qDebug() << "onResult";
    // Если в процесе получения данных произошла ошибка
    if(reply->error())
    {
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    }
    else
    {
        // В противном случае создаём объект для работы с файлом
        QFile *file = new QFile("./gpi_about.dll");
        // Создаём файл или открываем его на перезапись ...
        if(file->open(QFile::WriteOnly))
        {
            qDebug() << "write about.dll";
            file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
            file->close();                  // закрываем файл
            qDebug() << "Downloading is completed";
            emit downloader_onReady(); // Посылаем сигнал о завершении получения файла
        }
    }
}
