#include "customwithdrawal.h"
#include "ui_customwithdrawal.h"
#include <QDebug>

CustomWithdrawal::CustomWithdrawal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomWithdrawal)
{
    ui->setupUi(this);
}

CustomWithdrawal::~CustomWithdrawal()
{
    delete ui;
}

// Alla oleva on kopsattu Sannan keyboard.cppstä

void CustomWithdrawal::numberClickHandler(QString n)
{
    qDebug() << "Handling button press " << n;

    enteredNumber += n;
    ui->lineEditAmount->setText(enteredNumber);

    qDebug() << "Entered number in string format is now " << enteredNumber;
}

void CustomWithdrawal::on_btn1_clicked()
{
    qDebug() << "Clicked 1" ;
    numberClickHandler("1");
}


void CustomWithdrawal::on_btn2_clicked()
{
    qDebug() << "Clicked 2" ;
    numberClickHandler("2");
}


void CustomWithdrawal::on_btn3_clicked()
{
    qDebug() << "Clicked 3";
    numberClickHandler("3");
}


void CustomWithdrawal::on_btn4_clicked()
{
    qDebug() << "Clicked 4";
    numberClickHandler("4");
}


void CustomWithdrawal::on_btn5_clicked()
{
    qDebug() << "Clicked 5";
    numberClickHandler("5");
}


void CustomWithdrawal::on_btn6_clicked()
{
    qDebug() << "Clicked 6";
    numberClickHandler("6");
}


void CustomWithdrawal::on_btn7_clicked()
{
    qDebug() << "Clicked 7";
    numberClickHandler("7");
}


void CustomWithdrawal::on_btn8_clicked()
{
    qDebug() << "Clicked 8" ;
    numberClickHandler("8");
}


void CustomWithdrawal::on_btn9_clicked()
{
    qDebug() << "Clicked 9";
    numberClickHandler("9");
}


void CustomWithdrawal::on_btn0_clicked()
{
    qDebug() << "Clicked 0" ;
    numberClickHandler("0");
}


void CustomWithdrawal::on_btnDelete_clicked()
{
    qDebug() << "Clicked Delete";
    enteredNumber.remove(enteredNumber.length()-1, 1);
    ui->lineEditAmount->setText(enteredNumber);
    qDebug() << "Entered number in string format is now " << enteredNumber;
}


void CustomWithdrawal::on_btnEnter_clicked()
{
    // tästä pitää saada lähetettyä enteredNumber amountiksi withdrawaliin
    qDebug() << "Clicked Enter";
    emit sendEnteredNumber(enteredNumber);
    this->close();
}


void CustomWithdrawal::on_btnExit_clicked()
{
    qDebug() << "Clicked Exit";
    // tähän koodi että palaa pääkirjautumisvalikkoon
}

