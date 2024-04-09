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

    // create model for the table view
    model = new QStandardItemModel();

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
    int length = formattedArray.size();

    // make sure you can't click into blank screens

    if (startIndex < length-5) {

        startIndex += 5;
        qDebug() << "Start index: " << startIndex;

        if (startIndex > -1) {
            model->clear();
            showInModel();
        }
    }

}

void Transactions::on_btnNext5_clicked()
{

    // make sure you can't click into negative indices

    if (startIndex > 0) {

        startIndex -= 5;
        qDebug() << "Start index: " << startIndex;

        if (startIndex > -1) {
            model->clear();
            showInModel();
    }
    }

}

void Transactions::showInModel()
{
    model->clear();

    // set headers for table view
    model->setHorizontalHeaderLabels({"Transaction Type", "Transaction Amount", "Transaction Time"});

    int itemsToAdd = qMin(5, formattedArray.size() - startIndex); // Ensure we don't exceed the array size
    // Loop through the desired range
    for (int i = startIndex; i < startIndex + itemsToAdd; ++i) {
        const QJsonValue &value = formattedArray.at(i); // Use at() method to avoid out-of-range access
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
    formattedArray = reversedArray;

    showInModel();

}

