#include "keyboard.h"
#include "ui_keyboard.h"
#include <QDebug>

Keyboard::Keyboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Keyboard)
{
    ui->setupUi(this);
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::numberClickHandler(QString n)
{
    qDebug() << "Handling button press " << n;

    enteredNumber += n;
    ui->txtEnteredNumber->setText(enteredNumber);

    qDebug() << "Entered number in string format is now " << enteredNumber;
}

void Keyboard::on_btn1_clicked()
{
    qDebug() << "Clicked 1" ;
    numberClickHandler("1");
}


void Keyboard::on_btn2_clicked()
{
    qDebug() << "Clicked 2" ;
    numberClickHandler("2");
}


void Keyboard::on_btn3_clicked()
{
    qDebug() << "Clicked 3";
    numberClickHandler("3");
}


void Keyboard::on_btn4_clicked()
{
    qDebug() << "Clicked 4";
    numberClickHandler("4");
}


void Keyboard::on_btn5_clicked()
{
    qDebug() << "Clicked 5";
    numberClickHandler("5");
}


void Keyboard::on_btn6_clicked()
{
    qDebug() << "Clicked 6";
    numberClickHandler("6");
}


void Keyboard::on_btn7_clicked()
{
    qDebug() << "Clicked 7";
    numberClickHandler("7");
}


void Keyboard::on_btn8_clicked()
{
    qDebug() << "Clicked 8" ;
    numberClickHandler("8");
}


void Keyboard::on_btn9_clicked()
{
    qDebug() << "Clicked 9";
    numberClickHandler("9");
}


void Keyboard::on_btn0_clicked()
{
    qDebug() << "Clicked 0" ;
    numberClickHandler("0");
}


void Keyboard::on_btnDelete_clicked()
{
    qDebug() << "Clicked Delete";
    enteredNumber.remove(enteredNumber.length()-1, 1);
    ui->txtEnteredNumber->setText(enteredNumber);
    qDebug() << "Entered number in string format is now " << enteredNumber;
}


void Keyboard::on_btnEnter_clicked()
{
    qDebug() << "Clicked Enter";
    emit sendEnteredNumber(enteredNumber);
    this->close();
}


void Keyboard::on_btnExit_clicked()
{
    qDebug() << "Clicked Exit";
    // tähän koodi että palaa pääkirjautumisvalikkoon
}

