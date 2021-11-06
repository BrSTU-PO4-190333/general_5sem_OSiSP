#include "mode.h"

QString mode::pluginName()
{
    return "mode 1";
}

QPalette mode::changeView()
{
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(Qt::color0));
    palette.setBrush(QPalette::ColorRole::WindowText, QBrush(Qt::black));
    return palette;
}
