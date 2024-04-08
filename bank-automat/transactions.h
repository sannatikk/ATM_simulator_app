#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>

namespace Ui {
class Transactions;
}

class Transactions : public QDialog
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = nullptr);
    ~Transactions();
    void setIdAccount(const QString &newIdAccount);

private slots:
    void setTransactionData(const QByteArray &newTransactionData);

    void on_btnLogout_clicked();
    void on_btnReturn_clicked();
    void on_btnPrevious5_clicked();
    void on_btnNext5_clicked();

private:
    Ui::Transactions *ui;
    QString idAccount;
    QByteArray transactionData;
};

#endif // TRANSACTIONS_H
