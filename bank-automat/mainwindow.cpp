#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RFID_dll = new RFIDReader(this);

    //Connect closeSerialSignal to library |exe -> RFIDReader
    connect(this, SIGNAL(closeSerialSignal()),
            RFID_dll, SLOT(handleCloseSerial()));
    QString url = Environment::getBaseUrl();
    LoginHandler_dll = new LoginHandler(url, this);

    //Connection for receiving response from LoginHandler
    connect(LoginHandler_dll, SIGNAL(responseSignal(QByteArray)),
            this,SLOT(handleLoginResponse(QByteArray)));

    //Connection for sending users login parameters to LoginHandler library
    connect(this, SIGNAL(loginSignal(QString,QString)),
            LoginHandler_dll, SLOT(handleLogin(QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSerialID(QString data)
{
    emit closeSerialSignal();

    serialID = data;

    PinUI_dll = new PinUI(this);
    PinUI_dll->show();

    connect(PinUI_dll, SIGNAL(pincodeSignal(QString)),
            this, SLOT(setPincode(QString)));
}

void MainWindow::setPincode(QString data)
{
    pincode = data;

    //Emit signal with parameters to loginHandler
    emit loginSignal(serialID, pincode);
}

void MainWindow::handleLoginResponse(QByteArray response)
{
    if(response=="-4078" || response.length()==0){

        qDebug() << "Database connection problem";
    }
    else{
        //If login success, token is returned
        if(response!="false"){
            qDebug() << "Login success";
            qDebug() << response;
            delete PinUI_dll;

            //Open userMenu
        }
        //If login fails
        else{
            qDebug() << "Card ID or Pincode doesn't match";
            qDebug() << response;
        }
    }
}

