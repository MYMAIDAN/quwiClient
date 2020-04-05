#include "login.h"
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QLoggingCategory>
#include <QJsonDocument>
#include <QJsonObject>

Login::Login(QObject *parent) :
    QObject(parent),
    mNetwrokManager( new QNetworkAccessManager(this) ),
    mNetworkRequest( new QNetworkRequest),
    mQmlEngine(new QQmlApplicationEngine(this))

{
    const QUrl url(QStringLiteral("qrc:/login.qml"));
    mQmlContext = mQmlEngine->rootContext();
    mQmlContext->setContextProperty("loginHandler",this);

    QObject::connect(mQmlEngine, &QQmlApplicationEngine::objectCreated,
                     this, [url](QObject *obj, const QUrl &objUrl) {
    }, Qt::QueuedConnection);

    QObject::connect(mNetwrokManager, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply){
        if( reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt() == 417 )
        {
            emit sendError("Invalid email or password");
        }
        if( reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt() == 200)
        {
            QJsonDocument item = QJsonDocument::fromJson(reply->readAll());
            QJsonObject object = item.object();
            qDebug() << object.value("token").toString();
            emit successLogin( object.value("token").toString() );
        }
    });
   mQmlEngine->load(url);
}

void Login::recieveData(QString email, QString passwd)
{
    mNetworkRequest->setUrl(QUrl("https://api.quwi.com/v2/auth/login"));
    mNetworkRequest->setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,"application/json");
    QVariantMap parameter;
    parameter["email"] =  email;
    parameter["password"] = passwd;
    mNetwrokManager->post(*mNetworkRequest,QJsonDocument::fromVariant(parameter).toJson());
}
