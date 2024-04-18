#ifndef ACCOUNTSELECT_H
#define ACCOUNTSELECT_H

#include "environment.h"
#include <QDialog>
#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class AccountSelect;
}

class AccountSelect : public QDialog
{
    Q_OBJECT

public:
    explicit AccountSelect(QWidget *parent = nullptr);
    ~AccountSelect();

    void setWebToken(const QByteArray &newWebToken);
    void setAccountIDs(const QJsonArray &newAccountIDs);
    void setDebitAccount(const QString &newDebitAccount);
    void setCreditAccount(const QString &newCreditAccount);

signals:
    void accountIDsChangedSignal();
    void logoutSignal();

private slots:
    void handleCardTypeRequest();
    void setAccountsSlot(QNetworkReply *reply);
    void on_btnDebit_clicked();
    void on_btnCredit_clicked();
    void on_btnLogout_clicked();

private:
    Ui::AccountSelect *ui;
    QNetworkAccessManager *accountManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray webToken;
    QJsonArray accountIDs;
    QString debitAccount;
    QString creditAccount;

};

#endif // ACCOUNTSELECT_H
