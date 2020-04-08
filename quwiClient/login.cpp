#include "login.h"
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QLoggingCategory>
#include <QJsonDocument>
#include <QJsonObject>

Login::Login(QObject *parent) :
    QObject(parent),
    mQmlEngine(new QQmlApplicationEngine(this))

{
    const QUrl url(QStringLiteral("qrc:/login.qml"));
    mQmlContext = mQmlEngine->rootContext();
    mQmlContext->setContextProperty("loginHandler",this);

    QObject::connect(mQmlEngine, &QQmlApplicationEngine::objectCreated,
                     this, [url](QObject *obj, const QUrl &objUrl) {
    }, Qt::QueuedConnection);

   mQmlEngine->load(url);
}

void Login::recieveData(QString email, QString passwd)
{
    emit authorization(email,passwd);
    qDebug() << "Hello";
}

void Login::authorizationRequestFinished(EAuthorizationStatus status)
{
    switch (status)
    {
    case EAuthorizationStatus::eOK:
    {
        emit authorizationSuccess();
        emit closeWindow();
        qDebug() << "OK";
        break;
    }
    case EAuthorizationStatus::eAuthorizationError:
    {
      emit sendError("Invalid email or password");
      break;
    }

    }
}
