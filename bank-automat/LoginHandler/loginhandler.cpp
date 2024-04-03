#include "loginhandler.h"

LoginHandler::LoginHandler(QString url, QObject * parent) : QObject(parent)
{
    qDebug() << "LoginHandler created";
    baseUrl = url;
    qDebug() << "Backend base URL: " << baseUrl;
}

void LoginHandler::handleLogin(QString serialID, QString pincode)
{
    QJsonObject jsonObj;
    jsonObj.insert("id_card",serialID);
    jsonObj.insert("pincode",pincode);

    QString site_url=baseUrl+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void LoginHandler::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();

    emit responseSignal(response_data);

    reply->deleteLater();
    loginManager->deleteLater();
}
