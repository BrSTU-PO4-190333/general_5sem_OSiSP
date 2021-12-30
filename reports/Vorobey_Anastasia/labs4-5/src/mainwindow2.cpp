#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
//#include <about/include/about.h>
//#include <helper_2/include/helper_2.h>
//#include <help_class/include/mybutton.h>
#include <QFontDialog>
#include <QSettings>

void MainWindow::menu_style_game()
{
    bool Changed;
        QFont newFont = QFontDialog::getFont(&Changed);
        if (Changed) {
            QApplication::setFont(newFont);
            QSettings settings(this);
            settings.setValue("VIEWF", newFont);
        }

}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mClient = new ClientStuff("localhost", 6547, 6788);
    connect(this->mClient, &ClientStuff::hasReadSome, this, &MainWindow::receivedSomething);

    this->mTimerUpdates = new QTimer(this);
    connect(this->mTimerUpdates, SIGNAL(timeout()), this, SLOT(on_CheckUpdateButton_clicked()));
    this->mTimerUpdates->start(20000);

    ui->setupUi(this);
    //ui->pushButton_2->setText(Exit());
   // ui->label->setText(ButtonName());
    ui->Win->setVisible(false);
    ui->Lose->setVisible(false);
    scene = new QGraphicsScene(0, 0, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);
    //scene->addPixmap(QPixmap(":/img/img/background"));
    scene->addPixmap(QPixmap(":/img2/img2/background"));

   // scene->addPixmap(QPixmap("D:/LABS/OOTPiSP/game/pd2-pacman/img2/background"));

    ui->graphicsView->setScene(scene);
    for(int i = 0; i < 29; i++){
        for(int j = 0; j < 26; j++){
            Smallpoint[i][j] = new smallpoint(18 + j * 28.5, 8 + i * 26.1, i, j);
            scene->addItem(Smallpoint[i][j]);
        }
    }

    QMenu* menu_style = new QMenu("&Style");
    QAction* menu_style_action = new QAction("&Style",menu_style);
    menu_style->addAction(menu_style_action);
    menu_style_action->setShortcut(QKeySequence(Qt::Key_F6));
    menuBar()->addMenu(menu_style);
    connect(menu_style_action, &QAction::triggered, this, &MainWindow::menu_style_game);

    setVersion(getDefaultVersion());

    smallpointNum = 0;
    Bigpoint[0] = new bigpoint();
    Bigpoint[0]->setPos(18, 60.2);
    scene->addItem(Bigpoint[0]);
    Bigpoint[1] = new bigpoint();
    Bigpoint[1]->setPos(730.5, 60.2);
    scene->addItem(Bigpoint[1]);
    Bigpoint[2] = new bigpoint();
    Bigpoint[2]->setPos(18, 582.2);
    scene->addItem(Bigpoint[2]);
    Bigpoint[3] = new bigpoint();
    Bigpoint[3]->setPos(730.5, 582.2);
    scene->addItem(Bigpoint[3]);
    bigpointNum = 0;
    Pacman = new pacman();
    Pacman->setPos(376, 576);
    Pacman->setFlag(QGraphicsItem::ItemIsFocusable);
    Pacman->setFocus();
    scene->addItem(Pacman);
    ghost1 = new red();
    scene->addItem(ghost1);
    ghost2 = new pink();
    scene->addItem(ghost2);
    ghost3 = new cyan();
    scene->addItem(ghost3);
    ghost4 = new orange();
    scene->addItem(ghost4);
    point = new QLabel(this);
    point->setGeometry(0, 0, 49, 17);
    point->setFont(QFont("Ubuntu Regular", 14));
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    point->setPalette(pa);
    point->setVisible(false);

    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(allMove()));
    timer1->start(13);
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(allChangePics()));
    timer2->start(100);
    timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(bigpointChangePics()));
    timer3->start(200);
    modeRed = modePink = modeCyan = modeOrange = 0;
    addpoint = 200;
    pause = false;
    isBonus2 = false;
    timer8 = new QTimer(this);
    timer8->setSingleShot(true);
    connect(timer8, SIGNAL(timeout()), this, SLOT(pauseTime()));
    timer8->start(2000);
    timer9 = new QTimer(this);
    connect(timer9, SIGNAL(timeout()), this, SLOT(slowMove()));
    timer9->start(26);
    timer10 = new QTimer(this);
    timer10->setSingleShot(true);
    connect(timer10, SIGNAL(timeout()), this, SLOT(cyanStartSlot()));
    timer10->start(7000);
    timer11 = new QTimer(this);
    timer11->setSingleShot(true);
    connect(timer11, SIGNAL(timeout()), this, SLOT(orangeStartSlot()));
    timer11->start(17000);

    pause = true;
    slowRed = false;
    slowPink = slowCyan = slowOrange = true;

}

void MainWindow::allMove(){
    if(!pause){
        Pacman->move();
        if(modeRed == 0 && !slowRed)
            ghost1->move();
        if(modePink == 0 && !slowPink)
            ghost2->move();
        if(modeCyan == 0 && !slowCyan)
            ghost3->move();
        if(modeOrange == 0 && !slowOrange)
            ghost4->move();
        for(int i = 0; i < 29; i++){
            for(int j = 0; j < 26; j++){
                bool isCollided = Pacman->collidesWithItem(Smallpoint[i][j]);
                if(isCollided){
                    Smallpoint[i][j]->collide();
                    ui->lcdNumber->display(ui->lcdNumber->value() + 10);
                    smallpointNum++;
                }
            }
        }
        for(int i = 0; i < 4; i++){
            bool isCollided = Pacman->collidesWithItem(Bigpoint[i]);
            if(isCollided){
                if(!q.empty()){
                    int temp = q.front();
                    q.pop_front();
                    delete timer4[temp];
                    delete timer5[temp];
                    delete timer6[temp];
                    delete timer7[temp];
                    addpoint = 200;
                    isBonus2 = false;
                }
                Bigpoint[i]->collide();
                ui->lcdNumber->display(ui->lcdNumber->value() + 50);
                modeRed = modePink = modeCyan = modeOrange = 1;
                timer4[i] = new QTimer(this);
                timer4[i]->setSingleShot(true);
                connect(timer4[i], SIGNAL(timeout()), this, SLOT(bonusTime()));
                timer5[i] = new QTimer(this);
                timer5[i]->setSingleShot(true);
                connect(timer5[i], SIGNAL(timeout()), this, SLOT(bonusTime2()));
                timer6[i] = new QTimer(this);
                connect(timer6[i], SIGNAL(timeout()), this, SLOT(flicker()));
                timer7[i] = new QTimer(this);
                connect(timer7[i], SIGNAL(timeout()), this, SLOT(ghostmove2()));
                timer4[i]->start(9000);
                timer5[i]->start(6500);
                timer6[i]->start(200);
                timer7[i]->start(20);
                q.push_back(i);
                bigpointNum++;
            }
        }
        bool isCollided1 = Pacman->collidesWithItem(ghost1);
        bool isCollided2 = Pacman->collidesWithItem(ghost2);
        bool isCollided3 = Pacman->collidesWithItem(ghost3);
        bool isCollided4 = Pacman->collidesWithItem(ghost4);
        if((isCollided1 && !modeRed) || (isCollided2 && !modePink) || (isCollided3 && !modeCyan) || (isCollided4 && !modeOrange)){
            pause = true;
            ui->Lose->setVisible(true);
        }
           //если кого-то съели
        if(isCollided1 && modeRed){
            modeRed = 0;
            point->setText(QString::number(addpoint));
            point->setGeometry(ghost1->x(), ghost1->y() + 30, 49, 17);
            point->setVisible(true);
            ui->lcdNumber->display(ui->lcdNumber->value() + addpoint);
            pause = true;
            timer8 = new QTimer(this);
            timer8->setSingleShot(true);
            connect(timer8, SIGNAL(timeout()), this, SLOT(getPointTime()));
            timer8->start(1000);
            ghost1->setPos(376, 342);
            ghost1->setDirection(0);
            slowRed = true;
            addpoint *= 2;
        }
        if(isCollided2 && modePink){
            modePink = 0;
            point->setText(QString::number(addpoint));
            point->setGeometry(ghost2->x(), ghost2->y() + 30, 49, 17);
            point->setVisible(true);
            ui->lcdNumber->display(ui->lcdNumber->value() + addpoint);
            pause = true;
            timer8 = new QTimer(this);
            timer8->setSingleShot(true);
            connect(timer8, SIGNAL(timeout()), this, SLOT(getPointTime()));
            timer8->start(1000);
            ghost2->setPos(376, 342);
            ghost2->setDirection(0);
            slowPink = true;
            addpoint *= 2;
        }
        if(isCollided3 && modeCyan){
            modeCyan = 0;
            point->setText(QString::number(addpoint));
            point->setGeometry(ghost3->x(), ghost3->y() + 30, 49, 17);
            point->setVisible(true);
            ui->lcdNumber->display(ui->lcdNumber->value() + addpoint);
            pause = true;
            timer8 = new QTimer(this);
            timer8->setSingleShot(true);
            connect(timer8, SIGNAL(timeout()), this, SLOT(getPointTime()));
            timer8->start(1000);
            ghost3->setPos(376, 342);
            ghost3->setDirection(0);
            slowCyan = true;
            addpoint *= 2;
        }
        if(isCollided4 && modeOrange){
            modeOrange = 0;
            point->setText(QString::number(addpoint));
            point->setGeometry(ghost4->x(), ghost4->y() + 30, 49, 17);
            point->setVisible(true);
            ui->lcdNumber->display(ui->lcdNumber->value() + addpoint);
            pause = true;
            timer8 = new QTimer(this);
            timer8->setSingleShot(true);
            connect(timer8, SIGNAL(timeout()), this, SLOT(getPointTime()));
            timer8->start(1000);
            ghost4->setPos(376, 342);
            ghost4->setDirection(0);
            slowOrange = true;
            addpoint *= 2;
        }
     //когда все съедены конец игры
        if(smallpointNum == 242 && bigpointNum == 4){
            pause = true;
            ui->Win->setVisible(true);
        }
    }
}

void MainWindow::allChangePics(){
    if(!pause){
        Pacman->changePics();
        if(modeRed == 0){
            ghost1->changePics();
        }
        else if(modeRed == 1){
            ghost1->changePics2();
        }
        else if(modeRed == 2){
            ghost1->changePics3();
        }
        if(modePink == 0){
            ghost2->changePics();
        }
        else if(modePink == 1){
            ghost2->changePics2();
        }
        else if(modePink == 2){
            ghost2->changePics3();
        }
        if(modeCyan == 0){
            ghost3->changePics();
        }
        else if(modeCyan == 1){
            ghost3->changePics2();
        }
        else if(modeCyan == 2){
            ghost3->changePics3();
        }
        if(modeOrange == 0){
            ghost4->changePics();
        }
        else if(modeOrange == 1){
            ghost4->changePics2();
        }
        else if(modeOrange == 2){
            ghost4->changePics3();
        }
    }
}

void MainWindow::bigpointChangePics(){
    if(!pause){
        Bigpoint[0]->changePics();
        Bigpoint[1]->changePics();
        Bigpoint[2]->changePics();
        Bigpoint[3]->changePics();
    }
}

void MainWindow::bonusTime(){
    int i = q.front();
    q.pop_front();
    modeRed = modePink = modeCyan = modeOrange = 0;
    isBonus2 = false;
    addpoint = 200;
    delete timer4[i];
    delete timer5[i];
    delete timer6[i];
    delete timer7[i];
}

void MainWindow::bonusTime2(){
    isBonus2 = true;
}

void MainWindow::flicker(){
    if(!pause){
        if(isBonus2){
            if(modeRed == 1){
                modeRed = 2;
            }
            else if(modeRed == 2){
                modeRed = 1;
            }
            if(modePink == 1){
                modePink = 2;
            }
            else if(modePink == 2){
                modePink = 1;
            }
            if(modeCyan == 1){
                modeCyan = 2;
            }
            else if(modeCyan == 2){
                modeCyan = 1;
            }
            if(modeOrange == 1){
                modeOrange = 2;
            }
            else if(modeOrange == 2){
                modeOrange = 1;
            }
        }
    }
}

void MainWindow::ghostmove2(){
    if(!pause){
        if((modeRed == 1 || modeRed == 2) && !slowRed)
            ghost1->move();
        if((modePink == 1 || modePink == 2) && !slowPink)
            ghost2->move();
        if((modeCyan == 1 || modeCyan == 2) && !slowCyan)
            ghost3->move();
        if((modeOrange == 1 || modeOrange == 2) && !slowOrange)
            ghost4->move();
    }
}

void MainWindow::getPointTime(){
    delete timer8;
    point->setVisible(false);
    pause = false;
}

void MainWindow::pauseTime(){
    delete timer8;
    ui->ready->setVisible(false);
    pause = false;
}

void MainWindow::slowMove(){
    if(!pause){
        if(slowRed)
            ghost1->move();
        if(slowPink)
            ghost2->move();
        if(slowCyan)
            ghost3->move();
        if(slowOrange)
            ghost4->move();
    }
    if(ghost1->x() == 376.0 && ghost1->y() == 272.0){
        slowRed = false;
    }
    if(ghost2->x() == 376.0 && ghost2->y() == 272.0){
        slowPink = false;
    }
    if(ghost3->x() == 376.0 && ghost3->y() == 272.0){
        slowCyan = false;
    }
    if(ghost4->x() == 376.0 && ghost4->y() == 272.0){
        slowOrange = false;
    }
}

void MainWindow::cyanStartSlot(){
    delete timer10;
    ghost3->setCyanStart();
}

void MainWindow::orangeStartSlot(){
    delete timer11;
    ghost4->setOrangeStart();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   // About();
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
   //About();
}
void MainWindow::on_CheckUpdateButton_clicked()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << "version:" + this->mVersion;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    mClient->tcpSocket->write(arrBlock);
}


void MainWindow::on_ConnectButton_clicked()
{
    mClient->connect2host();
}


void MainWindow::on_DisconnetButton_clicked()
{
    mClient->closeConnection();
}


void MainWindow::on_Version_clicked()
{
    QString version = QString("Version: %1").arg(mVersion);
    QMessageBox::information(this, tr("Info"), version);
}


void MainWindow::receivedSomething(QString msg)
{
    if(msg.contains("version:"))
    {
        QString version = msg.remove(0, 8);

        QMessageBox msgBox;
        if(version == this->mVersion)
        {
            msgBox.setText("No available updates");
            msgBox.exec();
        }
        else
        {
            msgBox.setText("New version " + version + " is available");
            msgBox.setInformativeText("Do you want to update app?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int res = msgBox.exec();

            if (res == QMessageBox::Yes)
            {
                this->setVersion(version);
                QByteArray arrBlock;
                QDataStream out(&arrBlock, QIODevice::WriteOnly);
                QString answer = "OK ON UPDATE";
                out << quint16(0) << answer;

                download();

                out.device()->seek(0);
                out << quint16(arrBlock.size() - sizeof(quint16));

                this->mClient->tcpSocket->write(arrBlock);
            }
        }
    }
    if(msg.contains("file:"))
    {
        download();

        for(int i = 0; i < 100; ++i)
        {
            this->mTimerBar->start(500);
        }
    }
}

QString MainWindow::getDefaultVersion()
{
    QString val;
    QFile file;
    file.setFileName("client.json");
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
    file.setFileName("client.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream( &file );
    stream << jsonString;
    file.close();

    mVersion = version;
}

QString MainWindow::getVersion()
{
    return mVersion;
}

void MainWindow::download()
{
    QFile::rename("D:\\101\\client\\pd2-pacman\\mainwindow.cpp", "D:\\101\\client\\pd2-pacman\\mainwindow.cpp.bak");
    QFile::rename("D:\\101\\client\\pd2-pacman\\pacman.cpp", "D:\\101\\client\\pd2-pacman\\pacman.cpp.bak");
    QFile::rename("D:\\101\\client\\pd2-pacman\\resources.qrc", "D:\\101\\client\\pd2-pacman\\resources.qrc.bak");

    QFile::copy("D:\\101\\server\\update\\mainwindow.cpp", "D:\\101\\client\\pd2-pacman\\mainwindow.cpp");
    QFile::copy("D:\\101\\server\\update\\pacman.cpp", "D:\\101\\client\\pd2-pacman\\pacman.cpp");
    QFile::copy("D:\\101\\server\\update\\resources.qrc", "D:\\101\\client\\pd2-pacman\\resources.qrc");
}
