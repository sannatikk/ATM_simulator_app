#include "transactions.h"
#include "ui_transactions.h"
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimeZone>
#include <QDateTime>

Transactions::Transactions(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Transactions)
{
    ui->setupUi(this);
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::on_btnReturn_clicked()
{
    delete this;
}

void Transactions::on_btnPrevious5_clicked()
{

}

void Transactions::on_btnNext5_clicked()
{

}

void Transactions::setIdAccount(const QString &newIdAccount)
{
    idAccount = newIdAccount;
    ui->txtAccountTransactions->setText("Account " +idAccount+ " transactions:");
}

void Transactions::setTransactionData(const QByteArray &newTransactionData)
{
    transactionData = newTransactionData;
    qDebug() << "Transaction data: " << transactionData;

    // parse into json document
    QJsonDocument jsonDoc = QJsonDocument::fromJson(transactionData);
    // extract array
    QJsonArray jsonArray = jsonDoc.array();

    // loop through array to fix weird timestamp
    for (QJsonValueRef value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QString transactionTime = obj["transaction_time"].toString();
            transactionTime.replace('T', ' ').replace(".000Z", "");
            obj["transaction_time"] = transactionTime;
            value = obj;
        }
    }

    // create new array to store items in reverse order
    QJsonArray reversedArray;
    // loop through the original array in reverse order and append items to the reverse array
    for (int i = jsonArray.size() - 1; i >= 0; --i) {
        reversedArray.append(jsonArray.at(i));
    }
    // update original array
    jsonArray = reversedArray;

    // create model for the table view
    QStandardItemModel *model = new QStandardItemModel();

    // set headers for table view
    model->setHorizontalHeaderLabels({"Transaction Type", "Transaction Amount", "Transaction Time"});

    // loop through array
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            const QJsonObject obj = value.toObject();

            // extract wanted fields
            QString transactionType = obj["transaction_type"].toString();
            QString transactionAmount = obj["transaction_amount"].toString();
            QString transactionTime = obj["transaction_time"].toString();

            // create qstandarditem for each field
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(transactionType);
            rowItems << new QStandardItem(transactionAmount);
            rowItems << new QStandardItem(transactionTime);

            // add row to model
            model->appendRow(rowItems);
        }
    }
    // send model to tableview
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(2, Qt::DescendingOrder);
    //ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

