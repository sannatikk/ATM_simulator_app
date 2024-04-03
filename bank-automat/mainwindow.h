#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rfidreader.h"
#include "pinui.h"
#include "loginhandler.h"
#include "environment.h"
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

    //void reset();

signals:
    void closeSerialSignal();
    void openSerialSignal();
    void loginSignal(QString, QString);

private slots:
    void setSerialID(QString);
    void setPincode(QString);
    void handleLoginResponse(QByteArray);

private:
    Ui::MainWindow *ui;
    RFIDReader *RFID_dll;
    PinUI *PinUI_dll;
    LoginHandler *LoginHandler_dll;

    QString serialID;
    QString pincode;
};
#endif // MAINWINDOW_H
