#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "field.h"
#include "qpushbuttonwithid.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();
    void handleButton();
    void onRightClicked();

private:
    Ui::MainWindow *ui;
    int width_val;
    int height_val;
    int diff_val;
    Field f;
    QList<QPushButtonWithId*> *buttons;
    bool gamerunning = false;
    void roundhandler(int);
    void handleClick(int);
    void setColor(int);
    void revealall();
    void checkforwin();


};
#endif // MAINWINDOW_H
