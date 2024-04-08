#include "pinui.h"
#include "ui_pinui.h"

PinUI::PinUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinUI)
{
    ui->setupUi(this);

    connect(ui->loginButton, SIGNAL(clicked(bool)),
            this, SLOT(handleButtonClick()));
}

PinUI::~PinUI()
{
    delete ui;
}

void PinUI::handleButtonClick()
{
    qDebug() << "Login button pressed";
    ui->loginButton->setText("Logging in...");

    emit pincodeSignal(enteredNumber);
}

void PinUI::handleNumberClick(QString n)
{
    enteredNumber += n;

    stars.clear();

    for (int i = 0; i < enteredNumber.length(); i++) {
        stars += "*";
    }

    ui->lineEdit->setText(stars);

    qDebug() << "Entered number in string format is now " << enteredNumber;
}

void PinUI::on_btn1_clicked()
{
    handleNumberClick("1");
}

void PinUI::on_btn2_clicked()
{
    handleNumberClick("2");
}

void PinUI::on_btn3_clicked()
{
    handleNumberClick("3");
}

void PinUI::on_btn4_clicked()
{
    handleNumberClick("4");
}

void PinUI::on_btn5_clicked()
{
    handleNumberClick("5");
}

void PinUI::on_btn6_clicked()
{
    handleNumberClick("6");
}

void PinUI::on_btn7_clicked()
{
    handleNumberClick("7");
}

void PinUI::on_btn8_clicked()
{
    handleNumberClick("8");
}

void PinUI::on_btn9_clicked()
{
    handleNumberClick("9");
}

void PinUI::on_btn0_clicked()
{
    handleNumberClick("0");
}

void PinUI::on_btnBackspace_clicked()
{
    qDebug() << "Clicked backspace";
    enteredNumber.remove(enteredNumber.length()-1, 1);
    stars.remove(stars.length()-1, 1);
    ui->lineEdit->setText(stars);
    qDebug() << "Entered number in string format is now " << enteredNumber;
}

void PinUI::on_btnQuit_clicked()
{
    qDebug() << "Clicked Quit";
    this->close();
    // tähän jokin signaali, että kun klikataan niin jokin mainwindow:n reset-funktio tapahtuu ja kaikki nollaantuu alkutilaan?
}

