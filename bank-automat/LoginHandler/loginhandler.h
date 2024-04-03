#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "LoginHandler_global.h"
#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class LOGINHANDLER_EXPORT LoginHandler : public QObject
{
    Q_OBJECT
public:
    LoginHandler(QString, QObject * parent = nullptr);

signals:
    void responseSignal(QByteArray);

private slots:
    void handleLogin(QString, QString);
    void loginSlot(QNetworkReply *reply);

private:
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QString baseUrl;
};

#endif // LOGINHANDLER_H
