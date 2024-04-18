#include "balance.h"
#include "ui_balance.h"
#include "mainwindow.h"
#include "usermenu.h"

Balance::Balance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Balance)
{
    ui->setupUi(this);
    networkManager = new QNetworkAccessManager(this);
    connect(this, SIGNAL(getBalanceSignal()),
            this, SLOT(fetchAccountDetails()));
    connect(networkManager, &QNetworkAccessManager::finished, this, &Balance::onNetworkReply);
}

Balance::~Balance() {
    delete ui;
}

void Balance::setBalance(float newBalance) {
    balance = newBalance;
    ui->balanceAmountLabel->setText(QString::number(balance, 'f', 2) + "€");
}

void Balance::fetchAccountDetails() {
    qDebug() << "Trying to make request for Balance for user: " << idAccount;
    QString site_url = Environment::getBaseUrl() + "/creditlimit/"+idAccount;
    QNetworkRequest request(site_url);
    QByteArray myToken = "Bearer " + webToken;
    request.setRawHeader("Authorization", myToken);
    networkManager->get(request);
}

void Balance::setIdAccount(const QString &newIdAccount)
{
    idAccount = newIdAccount;
}

void Balance::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;

    emit getBalanceSignal();
}

void Balance::onNetworkReply(QNetworkReply *reply) {
    qDebug() << "Reply in onNetWorkReply";

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();

    QString jsonResponse = QString::fromUtf8(responseData);
    jsonResponse.remove("\"");
    qDebug() << jsonResponse;
    float creditlimit = jsonResponse.toFloat();

    // onko creditLimit suurempi kuin 0
    if (creditlimit > 0) {
        ui->limitAmountLabel->setText(QString::number(creditlimit, 'f', 2) + "€");
    } else {
        ui->limitAmountLabel->setText("--");
    }

    float availableForWithdraw = balance + creditlimit;
    int withdrawableAmount = calculateWithdrawableAmount(availableForWithdraw);
    ui->availableAmountLabel->setText(QString::number(withdrawableAmount) + ".00€");

    reply->deleteLater();
}

int Balance::calculateWithdrawableAmount(float amount) {
    int num = amount;

    while (true) {
        if (num % 20 == 0 || num % 50 == 0) {
            break;
        }
        bool found = false;
        for (int num20 = 0; num20 <= num / 20; num20++) {
            for (int num50 = 0; num50 <= num / 50; num50++) {
            if ((num20 * 20 + num50 * 50) == num) {
                found = true;
                break;
            }
        }
        if (found) break;
    }
    if (found) break;
    num -= 1;
    }

    return num;
}




void Balance::on_btnBack_clicked() {
    close();
}

