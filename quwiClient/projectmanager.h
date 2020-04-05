#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQmlContext>
#include <QImage>

class ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(QString token,QObject *parent = nullptr);
private:
    ProjectManager(QObject *parent = nullptr);

private:
    QNetworkAccessManager*  mNetwrokManager{ nullptr };
    QNetworkRequest*        mNetworkRequest{ nullptr };
    QNetworkReply*          mNetworkReply{ nullptr };
    QQmlApplicationEngine*  mQmlEngine{ nullptr };
    QQmlContext*            mQmlContext{ nullptr };
    QString                 mToken;
};

#endif // PROJECTMANAGER_H
