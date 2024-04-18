#include "customwithdrawal.h"
#include "ui_customwithdrawal.h"
#include <QDebug>
#include <QString>

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

void CustomWithdrawal::numberClickHandler(QString n)
{
    enteredNumber += n;
    ui->lineEditAmount->setText(enteredNumber);

    amount = enteredNumber.toFloat();
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
    numberClickHandler("1");
}


void CustomWithdrawal::on_btn2_clicked()
{
    numberClickHandler("2");
}


void CustomWithdrawal::on_btn3_clicked()
{
    numberClickHandler("3");
}


void CustomWithdrawal::on_btn4_clicked()
{
    numberClickHandler("4");
}


void CustomWithdrawal::on_btn5_clicked()
{
    numberClickHandler("5");
}


void CustomWithdrawal::on_btn6_clicked()
{
    numberClickHandler("6");
}


void CustomWithdrawal::on_btn7_clicked()
{
    numberClickHandler("7");
}


void CustomWithdrawal::on_btn8_clicked()
{
    numberClickHandler("8");
}


void CustomWithdrawal::on_btn9_clicked()
{
    numberClickHandler("9");
}


void CustomWithdrawal::on_btn0_clicked()
{
    numberClickHandler("0");
}

void CustomWithdrawal::on_btnEnter_clicked()
{
    qDebug() << "Clicked Enter, amount = " << amount;

    int integerAmount = static_cast<int>(amount);
    if (integerAmount >= 20) {
        bool billsOk = withdrawable(integerAmount);
        if (billsOk == true)
        {
            emit sendEnteredNumber(amount);
            delete this;
        }
        else
        {
            ui->incorrectAmountLabel->setText("Invalid amount");
            enteredNumber = "";
            ui->lineEditAmount->setText(enteredNumber);
        }
    }
    else
    {
        ui->incorrectAmountLabel->setText("Minimum withdrawable amount is 20€");
        enteredNumber = "";
        ui->lineEditAmount->setText(enteredNumber);
    }
}

void CustomWithdrawal::on_btnBackspace_clicked()
{
    enteredNumber.remove(enteredNumber.length()-1, 1);
    ui->lineEditAmount->setText(enteredNumber);
}

void CustomWithdrawal::on_btnReturn_clicked()
{
    delete this;
}



