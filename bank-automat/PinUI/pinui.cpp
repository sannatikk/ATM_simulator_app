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
    QString data;

    data = ui->lineEdit->text();

    emit pincodeSignal(data);
}
