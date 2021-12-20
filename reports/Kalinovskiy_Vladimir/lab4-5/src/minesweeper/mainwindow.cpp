#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>
#include <QInputDialog>
#include <QMapIterator>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    mClient = new ClientStuff("localhost", 6547, 6788);
    connect(this->mClient, &ClientStuff::hasReadSome, this, &MainWindow::receivedSomething);

this->mTimerUpdates = new QTimer(this);
    connect(this->mTimerUpdates, SIGNAL(timeout()), this, SLOT(on_CheckUpdateButton_triggered()));
   this->mTimerUpdates->start(10000);

   ui->setupUi(this);
   QWidget *w = new QWidget;
   setCentralWidget(w);
   setWindowTitle("Minesweeper");
   w->setStyleSheet("background-color:green");
   setVersion(getDefaultVersion());
   // layout-ok beállítása
   font.setFamily("Comic Sans MS");
   mainLayout = new QVBoxLayout;
   firstLayout = new QHBoxLayout;
   firstLayout->setSpacing(50);
   gameLayout = new QGridLayout;
   gameLayout->setSpacing(0);
   gameLayout->setContentsMargins(0, 0, 0, 0);
   mainLayout->addLayout(firstLayout);
   mainLayout->addLayout(gameLayout);
   w->setLayout(mainLayout);

   time = 0;
   disabledButtons = 0;
   difficulty = 0;
   endOfGame = false;

   difficulties = createComboBox();
   firstLayout->addWidget(difficulties);

   flags = new QLabel;
   font = flags->font();
   font.setPointSize(font.pointSize() + 8);
   flags->setFont(font);
   flags->setText("Flags: 10");
   firstLayout->addWidget(flags);

   timeLabel = new QLabel("0:0");
   timeLabel->setFont(font);
   timer = new QTimer;
   connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
   firstLayout->addWidget(timeLabel);

   showHighscores = new QPushButton("Highscores");
   showHighscores->setFont(font);
   showHighscores->setEnabled(false);
   connect(showHighscores, &QPushButton::clicked, this, [&](){showTop10(difficulty);});
   firstLayout->addWidget(showHighscores);

   resetButton = new QPushButton("Reset");
   resetButton->setFont(font);
   connect(resetButton, &QPushButton::clicked,  this, [&](){reset();} );
   firstLayout->addWidget(resetButton);

   top10 = new QMessageBox;
   top10->setWindowTitle("Top 10");
   QPushButton* ok = new QPushButton("Ok");
   QPushButton* resetScores = new QPushButton("Reset highscores");
   connect(resetScores, &QPushButton::pressed, this, [&](){
       if(difficulty == 0){
           highscoresEasy.clear();
       }
       else if(difficulty == 1){
           highscoresMedium.clear();
       }
       else{
           highscoresHard.clear();
       }
       top10->setText("");
   });
   top10->addButton(resetScores, QMessageBox::ResetRole);
   top10->addButton(ok, QMessageBox::AcceptRole);


   setButtons(8, 10, 50);
   setBombs();
   setNumbers();

}

void MainWindow::setButtons(int n, int m, int size){
    buttonRows = n;
    buttonColumns = m;
    buttons = new MyButton**[n];
    buttonText = new QString*[n];
    for(int i=0; i<n; ++i){
        buttons[i] = new MyButton*[m];
        buttonText[i] = new QString[m];
    }
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            buttonText[i][j] = '-';
        }
    }

    int fontsize;
    switch (difficulty) {
        case 0:
            fontsize = 12;
            numberOfBombs = 10;
            numberOfFlags = 10;
            break;
        case 1:
            fontsize = 10;
            numberOfBombs = 40;
            numberOfFlags = 40;
            break;
        case 2:
            fontsize = 8;
            numberOfBombs = 99;
            numberOfFlags = 99;
            break;
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            buttons[i][j] = new MyButton(this);
            buttons[i][j]->setMinimumSize(size, size);
            buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            font = buttons[i][j]->font();
            font.setPointSize(font.pointSize() + fontsize);
            buttons[i][j]->setFont(font);
            buttons[i][j]->installEventFilter(this);
            connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
            connect(buttons[i][j], SIGNAL(rightClick()), this, SLOT(rightButtonClicked()));
            if( (i+j) % 2 == 0 ){
                buttons[i][j]->setStyleSheet("background-color:palegreen");
            }
            else{
                buttons[i][j]->setStyleSheet("background-color:limegreen");
            }
            gameLayout->addWidget(buttons[i][j], i, j);
        }
    }
}


void MainWindow::setBombs(){
    int nB = numberOfBombs;
    while(nB > 0){
        QTime time = QTime::currentTime();
        srand((uint)time.msec());
        int x = rand() % buttonRows;
        int y = rand() % buttonColumns;
        if (buttonText[x][y] == 'X'){
            continue;
        }
        buttonText[x][y] = 'X';
        --nB;
    }
}

void MainWindow::setNumbers(){
    for(int i=0; i<buttonRows; ++i){
        for(int j=0; j<buttonColumns; ++j){
            if(buttonText[i][j] == 'X'){
                continue;
            }
            int db = 0;
            for(int x=i-1; x<i+2; ++x){
                for(int y=j-1; y<j+2; ++y){
                    if(x<0 || x>buttonRows-1 || y<0 || y>buttonColumns-1){
                        continue;
                    }
                    if(buttonText[x][y] == "X"){
                        ++db;
                    }
                }
            }
            if(db != 0){      
                buttonText[i][j] = QString::number(db);
            }
        }
    }
}

void MainWindow::onFreeButtonClicked(int i, int j){
    if(i<0 || i>buttonRows-1 || j<0 || j>buttonColumns-1 || buttonText[i][j] == "X" || !buttons[i][j]->isEnabled()){
        return;
    }
    if(buttonText[i][j] == '-'){
        buttons[i][j]->setStyleSheet("background-color:azure");
        buttons[i][j]->setEnabled(false);
        ++disabledButtons;
        for(int x=i-1; x<i+2; ++x){
            for(int y=j-1; y<j+2; ++y){
               onFreeButtonClicked(x,y);
            }
        }
    }
    if(buttonText[i][j] != '-'){
        buttons[i][j]->setStyleSheet("background-color:wheat");
        buttons[i][j]->setText(buttonText[i][j]);
        buttons[i][j]->setEnabled(false);
        ++disabledButtons;
        return;
    }
}

void MainWindow::bombClicked(){
    endOfGame = true;
    timer->stop();
    flags->setText("You lost!");

    for(int i=0; i<buttonRows; ++i){
        for(int j=0; j<buttonColumns; ++j){
            if(buttonText[i][j] == "X"){
                buttons[i][j]->setStyleSheet("background-color:tomato");
                buttons[i][j]->setText(buttonText[i][j]);
            }
        }
    }
    showHighscores->setEnabled(true);
}

void MainWindow::win(){
    endOfGame = true;
    timer->stop();
    flags->setText("You win!");

    for(int i=0; i<buttonRows; ++i){
        for(int j=0; j<buttonColumns; ++j){
            if(buttonText[i][j] == "X"){
                buttons[i][j]->setStyleSheet("background-color:pink");
                buttons[i][j]->setText(buttonText[i][j]);
            }
            else{
                if(buttonText[i][j] == "-"){
                    buttons[i][j]->setStyleSheet("background-color:powderblue");
                }
                else{
                    buttons[i][j]->setStyleSheet("background-color:powderblue");
                    buttons[i][j]->setText(buttonText[i][j]);
                }
            }
        }
    }

    QString name = QInputDialog::getText(this, "Best Results", "Your Result: " +
                                         QString::number(time) + "s\nName:");
    if(difficulty == 0){
        highscoresEasy[time] = name;
        if(highscoresEasy.size() > 10){
           auto it = highscoresEasy.end();
           highscoresEasy.erase(--it);
        }
    }
    else if(difficulty == 1){
        highscoresMedium[time] = name;
        if(highscoresMedium.size() > 10){
           auto it = highscoresMedium.end();
           highscoresMedium.erase(--it);
        }
    }
    else{
        highscoresHard[time] = name;
        if(highscoresHard.size() > 10){
           auto it = highscoresHard.end();
           highscoresHard.erase(--it);
        }
    }
    showTop10(difficulty);
    showHighscores->setEnabled(true);
}

void MainWindow::reset(){
    endOfGame = false;
    time = 0;
    timer->stop();
    timeLabel->setText("0:0");
    showHighscores->setEnabled(false);
    disabledButtons = 0;

    if(difficulty == 0){
        clearButtons();
        setButtons(8, 10, 50);
        setBombs();
        setNumbers();
        flags->setText("Flags: 10");
    }
    else if(difficulty == 1){
        clearButtons();
        setButtons(14, 18, 40);
        setBombs();
        setNumbers();
        flags->setText("Flags: 40");
    }
    else{
        clearButtons();
        setButtons(20, 24, 30);
        setBombs();
        setNumbers();
        flags->setText("Flags: 99");
    }
}

void MainWindow::clearButtons(){
    while(gameLayout->count()){
       for(int i=0; i<gameLayout->count(); ++i){
           QWidget *tempWidget = gameLayout->itemAt(i++)->widget();
           mainLayout->removeWidget(tempWidget);
           delete tempWidget;
       }
    }
    delete buttons;
    delete buttonText;
}

void MainWindow::buttonClicked(){
    if(endOfGame){
        return;
    }
    if(!timer->isActive()){
        timer->start(80);
    }
    int x, y;
    QPushButton* tmp = (QPushButton*)sender();
    if(tmp->styleSheet() == "background-color:brown"){
        return;
    }
    for(int i=0; i<buttonRows; ++i){
        for(int j=0; j<buttonColumns; ++j){
            if(buttons[i][j] == tmp){
                x = i;
                y = j;
                break;
            }
        }
    }
    if(buttonText[x][y] != "X"){
         onFreeButtonClicked(x,y);
         if( disabledButtons == ((buttonRows*buttonColumns) - numberOfBombs) ){
             win();
         }
     }
     else{
         bombClicked();
     }
}

void MainWindow::rightButtonClicked(){
    if(!timer->isActive()){
        timer->start(80);
    }
    QPushButton* tmp = (QPushButton*)sender();
    int x, y;
    if(tmp->styleSheet() == "background-color:brown"){
        for(int i=0; i<buttonRows; ++i){
            for(int j=0; j<buttonColumns; ++j){
                if(buttons[i][j] == tmp){
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        if( (x+y) % 2 == 0 ){
            buttons[x][y]->setStyleSheet("background-color:palegreen");
        }
        else{
             buttons[x][y]->setStyleSheet("background-color:limegreen");
        }
        ++numberOfFlags;
        flags->setText("Flags: " + QString::number(numberOfFlags));
    }
    else{
        tmp->setStyleSheet("background-color:brown");
        --numberOfFlags;
        flags->setText("Flags: " + QString::number(numberOfFlags));
    }

}

void MainWindow::showTop10(int difficulty){
    if(difficulty == 0){
        QMapIterator<double, QString> it(highscoresEasy);
        top10->setText("Level: Easy\n\n");
        for(int i=1; i<11; ++i){
            if(it.hasNext()){
                it.next();
                top10->setText(top10->text() + QString::number(i) + ". " + it.value() + ": " + QString::number(it.key()) + "s\n");
            }
            else{
                break;
            }
        }
    }
    else if(difficulty == 1){
        QMapIterator<double, QString> it(highscoresMedium);
        top10->setText("Level: Medium\n\n");
        for(int i=1; i<11; ++i){
            if(it.hasNext()){
                it.next();
                top10->setText(top10->text() + QString::number(i) + ". " + it.value() + ": " + QString::number(it.key()) + "s\n");
            }
            else{
                break;
            }
        }
    }
    else{
        QMapIterator<double, QString> it(highscoresHard);
        top10->setText("Level: Hard\n\n");
        for(int i=1; i<11; ++i){
            if(it.hasNext()){
                it.next();
                top10->setText(top10->text() + QString::number(i) + ". " + it.value() + ": " + QString::number(it.key()) + "s\n");
            }
            else{
                break;
            }
        }
    }
    top10->exec();
}

QComboBox* MainWindow::createComboBox(){
    QComboBox* temp = new QComboBox;
    temp->setStyleSheet("background-color:aliceblue");
    font = temp->font();
    font.setPointSize(font.pointSize() + 8);
    temp->setFont(font);
    temp->addItem("Easy");
    temp->addItem("Medium");
    temp->addItem("Hard");
    connect(temp, SIGNAL(currentIndexChanged(int)), this, SLOT(difficultyChanged()));
    return temp;
}

void MainWindow::tick(){
    time += 0.1;
    timeLabel->setText(QString::number(time));
}

void MainWindow::difficultyChanged(){
    difficulty = difficulties->currentIndex();
    reset();
}



MainWindow::~MainWindow()
{

}




void MainWindow::on_CheckUpdateButton_triggered()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << "version:" + this->mVersion;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    mClient->tcpSocket->write(arrBlock);
}


void MainWindow::on_ConnectButton_triggered()
{
    mClient->connect2host();
}


void MainWindow::on_DisconnectButton_triggered()
{
    mClient->closeConnection();
}


void MainWindow::on_Version_triggered()
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
    QFile::rename("E:\\driapko\\minesweeper-qt-master\\mainwindow.cpp", "E:\\driapko\\minesweeper-qt-master\\mainwindow.cpp.bak");
    QFile::copy("C:\\Users\\User\\Downloads\\Telegram Desktop\\101\\101\\server\\update\\mainwindow.cpp", "E:\\driapko\\minesweeper-qt-master\\mainwindow.cpp");
}



