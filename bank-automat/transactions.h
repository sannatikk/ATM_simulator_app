#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QJsonArray>
#include <QDialog>
#include <QStandardItemModel>

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
    void on_btnReturn_clicked();
    void on_btnPrevious5_clicked();
    void on_btnNext5_clicked();

private:
    Ui::Transactions *ui;
    QString idAccount;
    QByteArray transactionData;
    QStandardItemModel *model;
    QJsonArray formattedArray;
    int startIndex = 0;
    void showInModel();
};

#endif // TRANSACTIONS_H
