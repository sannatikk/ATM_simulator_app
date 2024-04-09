#include "usermenu.h"
#include "ui_usermenu.h"
#include "environment.h"

UserMenu::UserMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserMenu)
{
    ui->setupUi(this);

    balanceManager = new QNetworkAccessManager(this);
    connect(balanceManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(balanceSlot(QNetworkReply*)));

    transactionManager = new QNetworkAccessManager(this);
    connect(transactionManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(transactionSlot(QNetworkReply*)));
}

UserMenu::~UserMenu()
{
    delete ui;
}

void UserMenu::transactionSlot(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();

    qDebug() << "Response Data:" << responseData;

    QJsonDocument json_doc = QJsonDocument::fromJson(responseData);

    // QJsonArray json_array = json_doc.array();
    // for (int i = 0; i < json_array.size(); ++i) {
    //     if (json_array[i].toString() == "/") {
    //         json_array.removeAt(i);
    //         --i; // Adjust index to account for removed element
    //     }
    // }
    // qDebug() << "Parsed array:" << json_array;

    reply->deleteLater();
}

void UserMenu::on_btnViewTransactions_clicked()
{
    QString site_url = Environment::getBaseUrl() + "/accounttransactions/" + idAccount;
    QNetworkRequest request(site_url);

    QByteArray myToken = "Bearer " + webToken;
    request.setRawHeader(QByteArray("Authorization"), myToken);

    // Send the request
    transactionManager->get(request);

    // create ViewTransactions class object
    // open ViewTransactions class form
}

void UserMenu::balanceSlot(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QString jsonResponse = QString::fromUtf8(responseData);
    jsonResponse.remove("\"");

    balance = jsonResponse.toDouble();

    qDebug() << "JSON Response:" << jsonResponse;
    qDebug() << "Balance: " << balance;

    reply->deleteLater();
}

void UserMenu::on_btnViewBalance_clicked()
{

    QString site_url = Environment::getBaseUrl() + "/balance/" + idAccount;
    QNetworkRequest request(site_url);

    QByteArray myToken = "Bearer " + webToken;
    request.setRawHeader(QByteArray("Authorization"), myToken);

    // Send the request
    balanceManager->get(request);

    // Balance *balancePtr = new Balance(this);
    // balancePtr->open();
    // balancePtr->setAmount(balance);
    // balancePtr->setWebToken(webToken);
    // balancePtr->setIdAccount(idAccount)
}

void UserMenu::on_btnWithdraw_clicked()
{
    // Withdrawal *withdrawalPtr = new Withdrawal(this);
    // withdrawalPtr->open();
    // withdrawalPtr->setWebToken(webToken);
    // withdrawalPtr->setIdAccount(idAccount);
}

void UserMenu::on_btnLogout_clicked()
{
    //close();
    // tähän jokin signaali, jolla pääsee jonkinlaiseen "reset"-funktioon?
    emit logoutSignal();
    delete this;
}

void UserMenu::setIdAccount(const QString &newIdAccount)
{
    idAccount = newIdAccount;
}

void UserMenu::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}
