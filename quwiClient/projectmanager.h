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

#include "public.h"

class ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(const SProjectInfo& projectInfo ,QString token,QObject *parent = nullptr);
private:
    ProjectManager(QObject *parent = nullptr);
public slots:
    void changeName(const QString& newName);
private:
    QNetworkAccessManager*  mNetwrokManager{ nullptr };
    QNetworkRequest*        mNetworkRequest{ nullptr };
    QNetworkReply*          mNetworkReply{ nullptr };
    QQmlApplicationEngine*  mQmlEngine{ nullptr };
    QQmlContext*            mQmlContext{ nullptr };
    QString                 mToken;
    SProjectInfo            mProjectInfo;
};

#endif // PROJECTMANAGER_H
