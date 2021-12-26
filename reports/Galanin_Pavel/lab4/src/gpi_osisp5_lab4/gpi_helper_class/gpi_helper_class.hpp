#ifndef GPI_HELPER_CLASS_HPP
#define GPI_HELPER_CLASS_HPP

#include "gpi_helper_class_global.h"
#include <QDebug>

class GPI_HELPER_CLASS_EXPORT gpi_helper_class
{
public:
    gpi_helper_class();
};

extern "C" GPI_HELPER_CLASS_EXPORT gpi_helper_class* gpi_create_gpi_helper_class()
{
   return new gpi_helper_class();
}

#endif // GPI_HELPER_CLASS_HPP
