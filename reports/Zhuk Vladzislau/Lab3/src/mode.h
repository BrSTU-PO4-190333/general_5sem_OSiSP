#ifndef MODE_H
#define MODE_H

#include <QObject>
#include <interface.h>

class Mode : public QObject, public Interface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "calendar.Interface" FILE "Interface.json")
    Q_INTERFACES(Interface)
public:
    Mode(QObject *parent =0);
    ~Mode();
    QString name();
    virtual QFont changeView();
};

#endif // MODE_H
