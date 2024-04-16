#ifndef USERMENU_H
#define USERMENU_H


#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace Ui {
class UserMenu;
}

class UserMenu : public QDialog
{
    Q_OBJECT

public:
    explicit UserMenu(QWidget *parent = nullptr);
    ~UserMenu();

    void setWebToken(const QByteArray &newWebToken);
    void setIdAccount(const QString &newIdaccount);

signals:
    void transactionDataSignal(QByteArray);
    void logoutSignal();

private slots:
    void on_btnViewBalance_clicked();
    void on_btnViewTransactions_clicked();
    void on_btnWithdraw_clicked();
    void on_btnLogout_clicked();
    void balanceSlot(QNetworkReply *reply);
    void transactionSlot(QNetworkReply *reply);

private:
    Ui::UserMenu *ui;
    QByteArray webToken;
    QString idAccount;
    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *transactionManager;
    double balance;
    QByteArray transactionResponseData;
};

#endif // USERMENU_H
