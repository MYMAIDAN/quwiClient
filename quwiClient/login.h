#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQmlContext>

#include "public.h"

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = nullptr);
signals:
    void sendError( QString error );
    void authorizationSuccess();
    void closeWindow();
    void authorization(const QString& email, const QString& password);

public slots:
   void recieveData( QString email, QString passwd );
   void authorizationRequestFinished(EAuthorizationStatus status);

private:
    QQmlApplicationEngine*  mQmlEngine{ nullptr };
    QQmlContext*            mQmlContext{ nullptr };


};

#endif // LOGIN_H
