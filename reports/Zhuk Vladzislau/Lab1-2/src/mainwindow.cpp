#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

bool remove_line(const char *filename, int index) {
    QVector<QString> vec;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
        QString str;
        str = file.readAll();
        vec = (str.split(QRegExp("[\n]")).toVector());
        vec.pop_back();
        if (vec.size() <= index)
            return false;
        vec.erase(vec.begin() + index);

        QFile out("list.txt");
                if (!out.open(QIODevice::WriteOnly))
                    return false;
        for (int i = 0; i < vec.size(); ++i) {
            out.write(vec[i].toStdString().data());
            out.write("\n");
        }
        out.close();
    return false;
}

void MainWindow::accept(int index) {
    int helpRow = ui->table_toDo->rowCount();
    helpRow--;
    QFile read("list.txt");
            if (!read.open(QIODevice::ReadOnly))
                return;
    if(ui->table_toDo->item(helpRow,0)->text() != "" && read.size() != 0) {
        ui->table_toDo->item(index,0)->setBackground(Qt::green);
        listAccept[currectList[row].toInt()] = '1';

        save.clear();

        currectList.clear();
        listData.clear();
        listTask.clear();

        QString buffer;
        buffer = read.readAll(); // Буфер
        QStringList aa = buffer.split(QRegExp("[-\n]"));
        aa.pop_back();

        for (int i = 0, j = 0; i < aa.size(); i += 3, j++) {
            int indD = i;
            int indT = i;
            indT +=2;
            listData.append(aa[indD]);
            save.append(listData[j]);
            save.append("-");
            save.append(listAccept[j]);
            save.append("-");
            listTask.append(aa[indT]);
            save.append(listTask[j]);
            save.append("\n");
        }

        QFile file("list.txt");
            if (!file.open(QIODevice::WriteOnly))
                return;
        for (int i = 0; i < save.size(); ++i) {
            file.write(save[i].toStdString().data());
        }
        file.close();

        loadingDoings();
    }
    read.close();
}

void MainWindow::loadingDoings() {
    noticeTextToday.clear();
    noticeTextOneDayNext.clear();
    noticeTextThreeDaysNext.clear();

    save.clear();
    ui->table_toDo->clear(); // Очистка таблицы
    ui->table_toDo->setRowCount(0); // Удаляем все строки таблицы
    currectDo = 0; // Обнуляем счетчик строк таблицы
    ui->table_toDo->setHorizontalHeaderLabels(QStringList() << tr(ui->calendarWidget->selectedDate().toString().toStdString().data()));

    currectList.clear();
    listData.clear();
    listAccept.clear();
    listTask.clear();

    QString buffer;
    QFile read("list.txt");
            if (!read.open(QIODevice::ReadOnly))
                return;

    if(read.size() != 0) {
        buffer = read.readAll(); // Буфер
        save = buffer.split('*');
        QStringList aa = buffer.split(QRegExp("[-\n]"));
        aa.pop_back();

        for (int i = 0; i < aa.size(); i += 3) {
            int indD = i;
            int indA = i;
            int indT = i;
            indA +=1;
            indT +=2;
            listData.append(aa[indD]);
            listAccept.append(aa[indA]);
            listTask.append(aa[indT]);
        }
    }

    for (int i = 0; i < listData.size(); ++i) {
        if(ui->calendarWidget->selectedDate().toString().toStdString().data()==listData[i]) {
            ui->table_toDo->setRowCount(ui->table_toDo->rowCount() + 1);
            currectList.append(QString::number(i));
            QTableWidgetItem * item;
            item = new QTableWidgetItem;
            item->setText(listTask[i]);
            ui->table_toDo->setItem(currectDo, 0, item);

            if(listAccept[i] == '1') {
                 ui->table_toDo->item(currectDo,0)->setBackground(Qt::green);
            }
            currectDo++;
        }
    }

    for (int i = 0; i < listData.size(); ++i) {
        if(DateNext.toString()==listData[i] && listAccept[i] != '1') { // Уведомления за день
            noticeTextOneDayNext += listTask[i];
            noticeTextOneDayNext += '\n';
        }
        if(DateThreeNext.toString()==listData[i] && listAccept[i] != '1') { // Уведомления за день
            noticeTextThreeDaysNext += listTask[i];
            noticeTextThreeDaysNext += '\n';
        }
        if(QDate::currentDate().toString() ==listData[i] && listAccept[i] != '1') { // Уведомления по текущей дате
            noticeTextToday += listTask[i];
            noticeTextToday += '\n';
        }
    }
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    currectDo = ui->table_toDo->rowCount(); // определяем количество уже записаных данных
    popUp = new PopUp();

    DateNext=QDate::currentDate();
    DateThreeNext=QDate::currentDate();
    DateNext = DateNext.addDays(1);
    DateThreeNext = DateThreeNext.addDays(3);

    loadingDoings();

    QStringList s;
    s.append(QDate::currentDate().toString());
    ui->table_toDo->setHorizontalHeaderLabels(s);

    ui->table_toDo->horizontalHeader()->setStretchLastSection(true); // по ширине строки

    if(noticeTextToday != "") {
         timer = new QTimer();
         connect(timer, SIGNAL(timeout()), this, SLOT(NoticeToday()));
         timer->start(1000); // И запустим таймер
    }
    else {
        if(noticeTextOneDayNext != "") {
            timerNextDay = new QTimer();
            connect(timerNextDay, SIGNAL(timeout()), this, SLOT(NoticeOneDayNext()));
            timerNextDay->start(1000); // И запустим таймер
        }
        else {
            if(noticeTextThreeDaysNext != "") {
                timerThreeNextDay = new QTimer();
                connect(timerThreeNextDay, SIGNAL(timeout()), this, SLOT(NoticeThreeDaysNext()));
                timerThreeNextDay->start(1000); // И запустим таймер
            }
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_calendarWidget_selectionChanged() {
    loadingDoings(); //Загрука задач из файла
}

void MainWindow::on_add_doFortable_clicked() {
    flag = true;

    if(ui->table_toDo->takeItem(currectList.size(), 0) == NULL) ui->table_toDo->setRowCount(ui->table_toDo->rowCount() + 1);

    QTableWidgetItem * item;
    item = new QTableWidgetItem;
    item->setText("");
    ui->table_toDo->setItem(currectDo, 0, item);
}

void MainWindow::on_showCurrectDate_clicked() {
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    loadingDoings();
}

void MainWindow::on_table_toDo_clicked(const QModelIndex &index) {
    row = index.row();
    if(currectList.size() < row)
    row = currectList[row].toInt();
}

void MainWindow::on_del_doFortable_clicked() {
    if(row >= 0 && ui->table_toDo->rowCount() > 0) remove_line("list.txt", row);
    loadingDoings();
}

void MainWindow::on_save_doFortable_clicked() {
    if(flag) {
        int helpRow = ui->table_toDo->rowCount();
        helpRow--;
        if(ui->table_toDo->item(helpRow,0)->text() != "") {
            QFile file("list.txt");
                    if (!file.open(QIODevice::WriteOnly))
                        return;
            for (int i = row; i < ui->table_toDo->rowCount(); i++) {
                save.append(ui->calendarWidget->selectedDate().toString().toStdString().data());
                save.append("-");
                save.append("0");
                save.append("-");
                save.append(ui->table_toDo->item(i,0)->text().toStdString().data());
                save.append("\n");
            }

            for (int i = 0; i < save.size(); ++i) {
                file.write(save[i].toStdString().data());
            }
            file.close();

            loadingDoings();
        }
    }
    flag = false;
}

void MainWindow::on_accept_clicked() {
    if(row >= 0 && ui->table_toDo->rowCount() > 0) accept(row);
    loadingDoings();
}

void MainWindow::NoticeToday() {
    popUp->setPopupText("Сегодня необходимо :\n" + noticeTextToday);
    popUp->show();
    timer->stop();


    if(noticeTextOneDayNext != "") {
        timerNextDay = new QTimer();
        connect(timerNextDay, SIGNAL(timeout()), this, SLOT(NoticeOneDayNext()));
        timerNextDay->start(1000); // И запустим таймер
    }
    else {
        if(noticeTextThreeDaysNext != "") {
            timerThreeNextDay = new QTimer();
            connect(timerThreeNextDay, SIGNAL(timeout()), this, SLOT(NoticeThreeDaysNext()));
            timerThreeNextDay->start(1000); // И запустим таймер
        }
    }
}

void MainWindow::NoticeThreeDaysNext() {
    popUp->setPopupText("Через 3 дня необходимо :\n" + noticeTextThreeDaysNext);
    popUp->show();
    timerThreeNextDay->stop();
}

void MainWindow::NoticeOneDayNext() {
    popUp->setPopupText("Завтра необходимо :\n" + noticeTextOneDayNext);
    popUp->show();


    timerNextDay->stop();
    if(noticeTextThreeDaysNext != "") {
        timerThreeNextDay = new QTimer();
        connect(timerThreeNextDay, SIGNAL(timeout()), this, SLOT(NoticeThreeDaysNext()));
        timerThreeNextDay->start(1000); // И запустим таймер
    }
}
