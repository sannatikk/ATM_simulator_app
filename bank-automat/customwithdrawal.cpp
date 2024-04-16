#include "customwithdrawal.h"
#include "ui_customwithdrawal.h"
#include <QDebug>
#include <QString>
#include <iostream>

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

    amount = enteredNumber.toFloat();

    qDebug() << "Entered number in float format is now " << amount;
}

bool CustomWithdrawal::withdrawable(int num)
{
    if (num % 20 == 0 || num % 50 == 0)
    {
        return true;
    }
    for (int num20 = 0; num20 <= num / 20; num20++)
    {
        for (int num50 = 0; num50 <= num / 50; num50++)
        {
            if((num20 * 20 + num50 * 50) == num)
            {
                return true;
            }
        }
    }
    return false;
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

void CustomWithdrawal::on_btnEnter_clicked()
{
    // tästä pitää saada lähetettyä enteredNumber amountiksi floattina withdrawalrequestiin
    qDebug() << "Clicked Enter";
    qDebug() << amount;

    int integerAmount = static_cast<int>(amount);
    bool billsOk = withdrawable(integerAmount);
    if (billsOk == true)
    {
        emit sendEnteredNumber(amount);
        delete this;
    }
    else
    {
        ui->incorrectAmountLabel->setText("Incorrect amount");
    }

}

void CustomWithdrawal::on_btnBackspace_clicked()
{
    qDebug() << "Clicked Backspace";
    enteredNumber.remove(enteredNumber.length()-1, 1);
    ui->lineEditAmount->setText(enteredNumber);
    qDebug() << "Entered number in string format is now " << enteredNumber;
}

void CustomWithdrawal::on_btnReturn_clicked()
{
    delete this;
}


