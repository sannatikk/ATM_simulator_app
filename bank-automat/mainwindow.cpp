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

    // HUOM TÄMÄN OLEN LISÄNNYT
    QString test_id = "0B00320D2B";
    setSerialID(test_id);
    // TÄHÄN LOPPUU LISÄTYT
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
    // note for below: error -61 is mac equivalent of widows error -4078
    if (response == "-61" || response == "-4078" || response.length()==0){

        qDebug() << "Database connection problem";
    }
    else{
        //If login success, token is returned
        if(response!="false"){
            qDebug() << "Login success";
            qDebug() << response;
            delete PinUI_dll;

            // tähän haara jossa tarkistetaan onko kortteja 1/2
            // jos 2 niin avataan erillinen valintaikkuna
            // muuten jatketaan suoraan main user menuun
            // open userMenu
        }
        //If login fails
        else{
            qDebug() << "Card ID or Pincode doesn't match";
            qDebug() << response;
        }
    }
}

