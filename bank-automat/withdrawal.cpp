#include "withdrawal.h"
#include "qnetworkaccessmanager.h"
#include "qnetworkrequest.h"
#include "ui_withdrawal.h"
#include "customWithdrawal.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

Withdrawal::Withdrawal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Withdrawal)
{
    ui->setupUi(this);

    withdrawalManager = new QNetworkAccessManager(this);
    connect(withdrawalManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(withdrawalSlot(QNetworkReply*)));
}

Withdrawal::~Withdrawal()
{
    delete ui;
}

void Withdrawal::on_btn20_clicked()
{
    qDebug()<<"20€ withdrawal pressed";
    amount = 20;
    handleAmount(amount);
}


void Withdrawal::on_btn40_clicked()
{
    qDebug()<<"40€ withdrawal pressed";
    amount = 40;
    handleAmount(amount);
}


void Withdrawal::on_btn50_clicked()
{
    qDebug()<<"50€ withdrawal pressed";
    amount = 50;
    handleAmount(amount);
}


void Withdrawal::on_btn80_clicked()
{
    qDebug()<<"80€ withdrawal pressed";
    amount = 80;
    handleAmount(amount);
}


void Withdrawal::on_btn100_clicked()
{
    qDebug()<<"100€ withdrawal pressed";
    amount = 100;
    handleAmount(amount);
}


void Withdrawal::on_btnOther_clicked()
{
    qDebug()<<"Other withdrawal pressed";

    CustomWithdrawal *customWithdrawal = new CustomWithdrawal(this);

    customWithdrawal->show();
    // tässä aukeaa uusi käyttöliittymä TARKISTA ETTÄ MÄTSÄÄ
}


void Withdrawal::on_btnReturn_clicked()
{
    qDebug()<<"Return button pressed";
    delete this;
}


void Withdrawal::on_btnLogOut_clicked()
{
    qDebug()<<"Log out pressed";
    delete this;
}

void Withdrawal::withdrawalSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();

    qDebug()<<"Response data, 1=ok" +response_data;

    QString jsonString(response_data);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonString.toUtf8());
    int responseDataInteger = jsonString.toInt();

    if (responseDataInteger == 0)
    {
        ui->responseLabel->setText("Withdrawal failed!");
    }
    else if (responseDataInteger == 1)
    {
        ui->responseLabel->setText("Withdrawal successful!");
    }
    else
    {
        ui->responseLabel->setText("Unknown response!");
    }

    reply->deleteLater();
    withdrawalManager->deleteLater();
}

void Withdrawal::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}


void Withdrawal::setIdAccount(const QString &newIdAccount)
{
    idAccount = newIdAccount;
}

void Withdrawal::handleAmount(float a)
{
    QJsonObject jsonObj;
    jsonObj.insert("id_account",idAccount);
    jsonObj.insert("amount",a);

    QString site_url=Environment::getBaseUrl()+"/withdraw/";
    QNetworkRequest request((site_url));

    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    reply = withdrawalManager->post(request, QJsonDocument(jsonObj).toJson());


}

