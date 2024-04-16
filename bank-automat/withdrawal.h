#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QDialog>
#include "environment.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

namespace Ui {
class Withdrawal;
}

class Withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit Withdrawal(QWidget *parent = nullptr);
    ~Withdrawal();

    void setIdAccount(const QString &newIdAccount);


    void setWebToken(const QByteArray &newWebToken);

//signals:
    //void handleAmount(float amount);
    //tähän tulee withdrawal.cppstä handleamountista signaali, jossa on parametrinä float amount

private slots:
    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn50_clicked();
    void on_btn80_clicked();
    void on_btn100_clicked();
    void on_btnOther_clicked();
    void on_btnReturn_clicked();
    void withdrawalSlot(QNetworkReply *reply);
    void handleAmount(float);
private:
    QString idAccount;
    QByteArray webToken;
    QNetworkReply *reply;
    QNetworkReply *withdrawalAmount;
    QByteArray response_data;
    float amount;

    QNetworkAccessManager *withdrawalManager;
    Ui::Withdrawal *ui;
};

#endif // WITHDRAWAL_H
