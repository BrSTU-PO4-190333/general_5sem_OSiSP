#include "about.h"
#include <QMessageBox>

void about()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About programm");
    msgBox.setText("The programm was developed by Gribovskij Dima\ncourse : 3\ngroup: PO-4\n2021");
    msgBox.exec();
}
