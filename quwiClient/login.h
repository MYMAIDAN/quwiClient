#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQmlContext>

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = nullptr);
signals:
    void sendError( QString error );
    void successLogin(QString token);
    void closeWindow();

public slots:
   void recieveData( QString email, QString passwd );



private:
    QNetworkAccessManager*  mNetwrokManager{ nullptr };
    QNetworkRequest*        mNetworkRequest{ nullptr };
    QNetworkReply*          mNetworkReply{ nullptr };
    QQmlApplicationEngine*  mQmlEngine{ nullptr };
    QQmlContext*            mQmlContext{ nullptr };


};

#endif // LOGIN_H
