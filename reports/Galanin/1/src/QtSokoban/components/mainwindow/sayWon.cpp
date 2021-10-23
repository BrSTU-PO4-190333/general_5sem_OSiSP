#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::sayWon()
{
    for (int i = 0; i < this->length; i += 1)
    {
        for (int j = 0; j < this->length; j += 1)
        {
            if (this->map[i][j] == finish)
            {
                return;
            }
        }
    }

    this->close();

    QMessageBox msgBox;

    QString StrWinWidth = QString::number(this->WinWidth);
    msgBox.setStyleSheet("QLabel{min-width: " + StrWinWidth + "px; }");
    msgBox.setText("You won");
    msgBox.setWindowTitle("You won");

    msgBox.exec();
}
