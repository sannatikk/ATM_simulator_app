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

void Transactions::on_btnLogout_clicked()
{
    this->close();
    // signaali metodiin jolla nollataan kaikki?
}


void Transactions::on_btnReturn_clicked()
{
    this->close();
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

    // Iterate over each object in the JSON array
    for (QJsonValueRef value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();

            // Modify transaction_time field
            QString transactionTime = obj["transaction_time"].toString();

            // Replace 'T' with a space and remove 'Z'
            transactionTime.replace('T', ' ').replace(".000Z", "");

            // Update the object with modified transaction_time
            obj["transaction_time"] = transactionTime;

            // Assign the modified object back to the JSON array
            value = obj;
        }
    }


    // create model for the table view
    QStandardItemModel *model = new QStandardItemModel();

    // set headers for table view
    model->setHorizontalHeaderLabels({"Transaction ID", "Transaction Type", "Transaction Amount", "Transaction Time"});

    // loop through array
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            const QJsonObject obj = value.toObject();

            // extract relevant fields
            QString idTransaction = QString::number(obj["id_transaction"].toInt());
            QString transactionType = obj["transaction_type"].toString();
            QString transactionAmount = obj["transaction_amount"].toString();
            QString transactionTime = obj["transaction_time"].toString();

            // create qstandarditem for each field
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(idTransaction);
            rowItems << new QStandardItem(transactionType);
            rowItems << new QStandardItem(transactionAmount);
            rowItems << new QStandardItem(transactionTime);

            // add row to model
            model->appendRow(rowItems);
        }
    }

    // set model to tableview
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}

