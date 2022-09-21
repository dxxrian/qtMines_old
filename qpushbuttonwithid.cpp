#include "qpushbuttonwithid.h"

QPushButtonWithId::QPushButtonWithId(int id)
{
    Id = id;
}

void QPushButtonWithId::setId(int id)
{
    Id = id;
}

int QPushButtonWithId::getId()
{
    return Id;
}

void QPushButtonWithId::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton){
        emit rightClicked();
    }else if(event->button()==Qt::LeftButton){
        emit leftClicked();
    }else{}
}
