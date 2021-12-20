#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setText("Программу сделал студент группы ПО-4 Жук Владислав\nПрограмма - Ежидневником");
    msgBox.exec();
}
