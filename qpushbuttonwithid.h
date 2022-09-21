#ifndef QPUSHBUTTONWITHID_H
#define QPUSHBUTTONWITHID_H

#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>

class QPushButtonWithId : public QPushButton
{
    Q_OBJECT
public:
    QPushButtonWithId(int id);
    void setId(int id);
    int getId();
    void mousePressEvent(QMouseEvent *event);


signals:
    void rightClicked();
    void leftClicked();

private:
    int Id;

};

#endif // QPUSHBUTTONWITHID_H
