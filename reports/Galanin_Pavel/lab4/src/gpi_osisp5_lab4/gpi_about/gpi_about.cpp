#include "gpi_about.hpp"

void gpi_about()
{
    QMessageBox gpi_mb;
    gpi_mb.setWindowTitle("О программе");
    gpi_mb.setText(
        "Программу разработал \n"
        "студент 3-его курса \n"
        "факультета ЭИС \n"
        "группы ПО-4(1) \n"
        "Галанин Павел \n"
        "(декабрь 2021) \n"
        " \n"
        "Хорошей игры! \n"
    );
    gpi_mb.exec();
}
