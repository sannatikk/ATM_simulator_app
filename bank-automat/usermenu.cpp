#include "usermenu.h"
#include "transactions.h"
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
    transactionResponseData = reply->readAll();
    qDebug() << "Response Data:" << transactionResponseData;

    Transactions *transactionsPtr = new Transactions(this);

    connect(this, SIGNAL(transactionDataSignal(QByteArray)),
            transactionsPtr, SLOT(setTransactionData(QByteArray)));

    transactionsPtr->setIdAccount(idAccount);
    transactionsPtr->show();

    emit transactionDataSignal(transactionResponseData);

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
    close();
    // tähän jokin signaali, jolla pääsee jonkinlaiseen "reset"-funktioon?
}

void UserMenu::setIdAccount(const QString &newIdAccount)
{
    idAccount = newIdAccount;
}

void UserMenu::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}
