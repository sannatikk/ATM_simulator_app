#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermenu.h"

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

    // these 2 lines are for bypassing rfid reader in case you don't have it for testing, change test_id value to the id_card you want
    QString test_id = "0B00320D2B"; // debit only card
    //QString test_id = "0600062E1F"; // credit only card
    //QString test_id = "06000D5C69"; // combination card
    setSerialID(test_id);
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
            this->setWebToken(response);
            //Request for checking is there 1 or 2 accounts in card
            QString site_url=Environment::getBaseUrl()+"/accountsincard/"+serialID;
            QNetworkRequest request((site_url));
            QByteArray myToken="Bearer "+webToken;
            request.setRawHeader(QByteArray("Authorization"), myToken);

            checkAccountsManager = new QNetworkAccessManager(this);
            connect(checkAccountsManager, SIGNAL(finished(QNetworkReply*)),
                    this, SLOT(checkAccountsSlot(QNetworkReply*)));

            reply = checkAccountsManager->get(request);
        }
        //If login fails
        else{
            qDebug() << "Card ID or Pincode doesn't match";
            qDebug() << response;
        }
    }
}

void MainWindow::checkAccountsSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();

    qDebug() << "Data received: " << response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray jsonArray = json_doc.array();

    int objectCount = jsonArray.size();

    /*Check number of accounts in card
    If one account -> UserMenu
    If 2 accounts -> AccountSelect*/
    qDebug() << "Number of accounts in card" << objectCount;
    if(objectCount > 1) {
        //accountSelect->
        AccountSelect *accountSelectPtr = new AccountSelect(this);
        accountSelectPtr->setWebToken(webToken);
        accountSelectPtr->setAccountIDs(jsonArray);
        accountSelectPtr->show();
    }
    else{

        // receive info as index within jsonarray
        qDebug() << "One account found: " << jsonArray[0];

        // pluck out jsonobject from array
        QJsonObject jsonObj = jsonArray[0].toObject();
        qDebug() << jsonObj;

        // convert to qstring
        QString accountID = jsonObj["id_account"].toString();
        qDebug() << "Account number in QString: " << accountID;

        // usermenu->
        UserMenu *userMenuPtr = new UserMenu(this);
        userMenuPtr->show();
        userMenuPtr->setWebToken(webToken);
        userMenuPtr->setIdAccount(accountID);
    }

    reply->deleteLater();
    checkAccountsManager->deleteLater();
}

void MainWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}
