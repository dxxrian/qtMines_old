#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttons = new QList<QPushButtonWithId*>;
    //setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Mines");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    if(gamerunning == false){
        ui->pushButton->setEnabled(false);
        f = Field(ui->spinBox_width->value(), ui->spinBox_height->value(), ui->spinBox_diff->value());
        buttons->reserve(f.getSize());
        gamerunning = true;
        if(f.generateField()<0){
            //qDebug() << "ERROR: Field generation failed.";
        }else{}
        //f.simpledraw();
        for(int r=0; r<f.getHeight(); r++){
            for(int c=0; c<f.getWidth(); c++){
                QPushButtonWithId* t = new QPushButtonWithId(r*f.getWidth()+c);
                t->setText("");
                buttons->append(t);
                buttons->at(r*f.getWidth()+c)->setStyleSheet("background-color: #DBDBDB"); //grey
                buttons->at(r*f.getWidth()+c)->setFixedWidth(1070/f.getWidth());
                buttons->at(r*f.getWidth()+c)->setFixedHeight(680/f.getHeight());
                buttons->at(r*f.getWidth()+c)->setText("");
                ui->gridLayout_2->addWidget(buttons->at(r*f.getWidth()+c),r,c);
                connect(buttons->at(r*f.getWidth()+c), &QPushButtonWithId::rightClicked, this, &MainWindow::onRightClicked);
                connect(buttons->at(r*f.getWidth()+c), &QPushButtonWithId::leftClicked, this, &MainWindow::handleButton);
            }
        }
    }else{
        //qDebug() << "Game is already running.";
    }
}

void MainWindow::handleButton()
{
    if(gamerunning == true){
        QPushButtonWithId *buttonSender = qobject_cast<QPushButtonWithId*>(sender());
        if(buttons->at(buttonSender->getId())->text() != "F")
        handleClick(buttonSender->getId());
    }else{
        //qDebug() << "Game is over.";
    }
}

void MainWindow::onRightClicked()
{
    if(gamerunning == true){
        QPushButtonWithId *buttonSender = qobject_cast<QPushButtonWithId*>(sender());
        int id=buttonSender->getId();
        if(buttons->at(id)->text() == ""){
            buttons->at(id)->setText("F");
            buttons->at(id)->setStyleSheet("background-color: #555555");//dark grey
            checkforwin();
        }else if(buttons->at(id)->text() == "B"){
        }else if(buttons->at(id)->text().toInt() != 0){
        }else if(buttons->at(id)->text() == "F"){
            buttons->at(id)->setText("");
            buttons->at(id)->setStyleSheet("background-color: #DBDBDB"); //grey
        }else{
            //qDebug() << "ERROR: Flag setting failed.";
        }
    }else{}
}

void MainWindow::handleClick(int id){
    int data = f.data.at(id);
    checkforwin();
    if(data == -1){
        //qDebug() << "Game over";
        gamerunning = false;
        revealall();
        //f.~Field();
        QMessageBox msgBox;
        msgBox.setText("Oh no! You have lost. You didn't do your job correctly and missed some mines. It is your fault that brave socialist soldiers will now lose their precious lives. This could have been prevented. An appropriate reprimand will be initiated.  Искренне Ваш, Союз Советских Социалистических Республик");
        msgBox.setWindowTitle("Ты неудачник");
        msgBox.exec();
    } else {
        buttons->at(id)->setText(QString::number(data));
        setColor(id);
        roundhandler(id);
    }
}

void MainWindow::checkforwin(){
    bool won = true;
    for(int i=0; i<f.getSize(); i++){
        if(buttons->at(i)->text() == "" || buttons->at(i)->text() == "B"){
            won=false;
            break;
        }else{
            if(buttons->at(i)->text() == "F" && f.data.at(i) != -1){
                won=false;
                break;
            }else{}
        }
    }
    if(won){
        QMessageBox msgBox;
        msgBox.setText("Yeah! You won. The Union of Soviet Socialist Republics is very proud of you. Many mothers of soldiers are happy, that they will be able to enjoy their sons a little bit longer in their exhaustive socialist life.");
        msgBox.setWindowTitle("Да здравствует наш лидер!!!");
        msgBox.exec();
        revealall();
    }else{}
}

void MainWindow::revealall(){
    for(int i=0; i<f.getSize(); i++){
        if(f.data.at(i) == -1){
            buttons->at(i)->setText("B");
        }else{
            buttons->at(i)->setText(QString::number(f.data.at(i)));
        }
        setColor(i);
    }
}

void MainWindow::roundhandler(int id){
    int data = f.data.at(id);
    buttons->at(id)->setText(QString::number(data));
    setColor(id);

    //Check for nearby mines
    bool reveal = true;
    int thisid;
    thisid=id+1;                //right
    if(id % f.getWidth() < f.getWidth()-1){ //right exists
        if(f.data.at(thisid) == -1){ //right is a mine
            reveal = false;
        } else {}
    } else {}
    thisid=id-1;                //left
    if(id % f.getWidth() != 0){ //left exists
        if(f.data.at(thisid) == -1){ //left is a mine
            reveal = false;
        } else {}
    } else {}
    thisid=id - f.getWidth();   //up
    if(id >= f.getWidth()){ //up exists
        if(f.data.at(thisid) == -1){ //up is a mine
            reveal = false;
        } else {}
    } else {}
    thisid=id + f.getWidth();   //down
    if(id < ((f.getHeight() - 1) * f.getWidth())){ //down exists
        if(f.data.at(thisid) == -1){ //down is a mine
            reveal = false;
        } else {}
    } else {}
    thisid=id - f.getWidth() + 1;//up-right
    if((id % f.getWidth() < f.getWidth()-1) && (id >= f.getWidth())){ //up-right exists
        if(f.data.at(thisid) == -1){ //up-right is a mine
            reveal = false;
        } else {}
    } else {}
    thisid=id - f.getWidth() - 1;//up-left
    if((id % f.getWidth() != 0) && (id >= f.getWidth())){ //up-left exists
        if(f.data.at(thisid) == -1){ //up-left is a mine
            reveal = false;
        } else {}
    } else {}
    thisid=id + f.getWidth() + 1;//down-right
    if((id % f.getWidth() < f.getWidth()-1) && (id < ((f.getHeight() - 1) * f.getWidth()))){ //down-right exists
        if(f.data.at(thisid) == -1){ //down-right is a mine
            reveal = false;
        } else {}
    } else {}
    thisid=id + f.getWidth() - 1;//down-left
    if((id % f.getWidth() != 0) && (id < ((f.getHeight() - 1) * f.getWidth()))){ //down-left exists
        if(f.data.at(thisid) == -1){ //down-left is a mine
            reveal = false;
        } else {}
    } else {}

    //Recursive revealing
    if(reveal==true){
        thisid=id+1;                //right
        if(id % f.getWidth() < f.getWidth()-1){ //right exists
            if(buttons->at(thisid)->text() == ""){ //right is not yet revealed
                handleClick(id+1);
            } else {}
        } else {}
        thisid=id-1;                //left
        if(id % f.getWidth() != 0){ //left exists
            if(buttons->at(thisid)->text() == ""){ //left is not yet revealed
                handleClick(id-1);
            } else {}
        } else {}
        thisid=id - f.getWidth();   //up
        if(id >= f.getWidth()){ //up exists
            if(buttons->at(thisid)->text() == ""){ //up is not yet revealed
                handleClick(id - f.getWidth());
            } else {}
        } else {}
        thisid=id + f.getWidth();   //down
        if(id < ((f.getHeight() - 1) * f.getWidth())){ //down exists
            if(buttons->at(thisid)->text() == ""){ //down is not yet revealed
                handleClick(id + f.getWidth());
            } else {}
        } else {}
        thisid=id - f.getWidth() + 1;//up-right
        if((id % f.getWidth() < f.getWidth()-1) && (id >= f.getWidth())){ //up-right exists
            if(buttons->at(thisid)->text() == ""){ //up-right is not yet revealed
                handleClick(id - f.getWidth() + 1);
            } else {}
        } else {}
        thisid=id - f.getWidth() - 1;//up-left
        if((id % f.getWidth() != 0) && (id >= f.getWidth())){ //up-left exists
            if(buttons->at(thisid)->text() == ""){ //up-left is not yet revealed
                handleClick(id - f.getWidth() - 1);
            } else {}
        } else {}
        thisid=id + f.getWidth() + 1;//down-right
        if((id % f.getWidth() < f.getWidth()-1) && (id < ((f.getHeight() - 1) * f.getWidth()))){ //down-right exists
            if(buttons->at(thisid)->text() == ""){ //down-right is not yet revealed
                handleClick(id + f.getWidth() + 1);
            } else {}
        } else {}
        thisid=id + f.getWidth() - 1;//down-left
        if((id % f.getWidth() != 0) && (id < ((f.getHeight() - 1) * f.getWidth()))){ //down-left exists
            if(buttons->at(thisid)->text() == ""){ //down-left is not yet revealed
                handleClick(id + f.getWidth() - 1);
            } else {}
        } else {}
    }
}



void MainWindow::setColor(int id){
    switch(f.data.at(id)){
        case(0):
            buttons->at(id)->setStyleSheet("background-color: #DFDFDF"); //grey
            break;
        case(1):
            buttons->at(id)->setStyleSheet("background-color: #AEEB1C");
            break;
        case(2):
            buttons->at(id)->setStyleSheet("background-color: #E5BB17");
            break;
        case(3):
            buttons->at(id)->setStyleSheet("background-color: #F58733");
            break;
        case(4):
            buttons->at(id)->setStyleSheet("background-color: #C90D32");
            break;
        case(5):
            buttons->at(id)->setStyleSheet("background-color: #D20A95");
            break;
        case(6):
            buttons->at(id)->setStyleSheet("background-color: #A506CB");
            break;
        case(7):
            buttons->at(id)->setStyleSheet("background-color: #3F03C5");
            break;
        case(8):
            buttons->at(id)->setStyleSheet("background-color: #0023BF");
            break;
        case(-1):
            buttons->at(id)->setStyleSheet("background-color: #FF0000"); //red
            break;
        default:
            buttons->at(id)->setStyleSheet("background-color: #DBDBDB"); //grey
            break;
    }
}
