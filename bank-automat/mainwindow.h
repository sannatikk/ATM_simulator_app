#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rfidreader.h"
#include "pinui.h"
#include "loginhandler.h"
#include "environment.h"
#include "accountselect.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setWebToken(const QByteArray &newWebToken);

signals:
    void closeSerialSignal();
    void openSerialSignal();
    void loginSignal(QString, QString);
    void loginResponseTextSignal(QString);

private slots:
    void setSerialID(QString);
    void setPincode(QString);
    void handleLoginResponse(QByteArray);
    void checkAccountsSlot(QNetworkReply *reply);
    void handleLogoutSlot();

private:
    Ui::MainWindow *ui;
    RFIDReader *RFID_dll;
    PinUI *PinUI_dll;
    LoginHandler *LoginHandler_dll;

    QNetworkAccessManager *checkAccountsManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray webToken;

    QString serialID;
    QString pincode;
};
#endif // MAINWINDOW_H
