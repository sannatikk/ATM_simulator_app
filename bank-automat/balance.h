#ifndef BALANCE_H
#define BALANCE_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class Balance;
}

class Balance : public QDialog {
    Q_OBJECT

public:
    explicit Balance(QWidget *parent = nullptr);
    ~Balance();

    void setBalance(float newBalance);
    int calculateWithdrawableAmount(float amount);
    void setWebToken(const QByteArray &newWebToken);

    void setIdAccount(const QString &newIdAccount);

signals:
    void getBalanceSignal();
private slots:
    void on_btnBack_clicked();
    void onNetworkReply(QNetworkReply *reply); // Korjattu nimi tässä
    void fetchAccountDetails();

private:
    Ui::Balance *ui;
    QByteArray webToken;
    QString idAccount;
    float balance;
    QNetworkAccessManager *networkManager;
};

#endif // BALANCE_H
