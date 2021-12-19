#ifndef MYBUTTON_H
#define MYBUTTON_H

#include "helper_class_global.h"
#include <QPushButton>
#include <QMouseEvent>


class HELPER_CLASS_EXPORT MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
    ~MyButton();

signals:
    void rightClicked();
    void leftClicked();
    void doubleClicked();

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // MYBUTTON_H
