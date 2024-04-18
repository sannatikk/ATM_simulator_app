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
#include <QMessageBox>

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
    qDebug()<<"20€ withdrawal clicked";
    amount = 20;
    handleAmount(amount);
}


void Withdrawal::on_btn40_clicked()
{
    qDebug()<<"40€ withdrawal clicked";
    amount = 40;
    handleAmount(amount);
}


void Withdrawal::on_btn50_clicked()
{
    qDebug()<<"50€ withdrawal clicked";
    amount = 50;
    handleAmount(amount);
}


void Withdrawal::on_btn80_clicked()
{
    qDebug()<<"80€ withdrawal clicked";
    amount = 80;
    handleAmount(amount);
}


void Withdrawal::on_btn100_clicked()
{
    qDebug()<<"100€ withdrawal clicked";
    amount = 100;
    handleAmount(amount);
}


void Withdrawal::on_btnOther_clicked()
{
    qDebug()<<"Other withdrawal clicked";

    CustomWithdrawal *customWithdrawal = new CustomWithdrawal(this);
    connect(customWithdrawal, SIGNAL(sendEnteredNumber(float)),
            this, SLOT(handleAmount(float)));
    customWithdrawal->open();
}


void Withdrawal::on_btnReturn_clicked()
{
    qDebug()<<"Return button clicked";
    delete this;
}

void Withdrawal::withdrawalSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();

    qDebug()<<"Response data, 1=ok: " +response_data;

    QString jsonString(response_data);
    int responseDataInteger = jsonString.toInt();

    if (responseDataInteger == 0)
    {
        ui->responseLabel->setText("Withdrawal failed");
        QMessageBox msgBox;
        msgBox.setText("Withdrawal failed due to insufficient funds");
        msgBox.exec();
        this->close();
    }
    else if (responseDataInteger == 1)
    {
        ui->responseLabel->setText("Withdrawal successful!");
        QMessageBox msgBox;
        msgBox.setText("Withdrawal successful!");
        msgBox.exec();
        this->close();
    }
    else
    {
        ui->responseLabel->setText("Unknown response");
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

    QString site_url=Environment::getBaseUrl()+"/withdraw";
    qDebug() << site_url;
    QNetworkRequest request((site_url));

    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = withdrawalManager->post(request, QJsonDocument(jsonObj).toJson());
}

