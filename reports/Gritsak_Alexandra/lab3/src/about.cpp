#include "about.h"

#include <QMessageBox>
void About()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About programm");
    msgBox.setText("The programm was developed by Gritsak Alexandra\nCourse : 3\nGroup: PO-4\n2021\nGood Game:)");
    msgBox.exec();
}
