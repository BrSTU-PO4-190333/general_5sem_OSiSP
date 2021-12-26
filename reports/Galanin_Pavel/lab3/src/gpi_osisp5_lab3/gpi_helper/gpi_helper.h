#ifndef GPI_HELPER_H
#define GPI_HELPER_H

#include "gpi_helper_global.h"
#include <QStringList>

extern "C" __declspec(dllexport)
QStringList gpi_get_1_level();

extern "C" __declspec(dllexport)
QStringList gpi_get_2_level();

extern "C" __declspec(dllexport)
QStringList gpi_get_3_level();

extern "C" __declspec(dllexport)
QStringList gpi_get_4_level();

#endif // GPI_HELPER_H
