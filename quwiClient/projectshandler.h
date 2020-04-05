#ifndef PROJECTSHANDLER_H
#define PROJECTSHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQmlContext>
#include <QImage>

#include "imagedownloader.h"

class ProjectsHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProjectsHandler(QObject *parent = nullptr);



public slots:
    void loadProjectsHandler(QString token);


private:

    struct SProjectInfo
    {
        QString name;
        QUrl    logoUrl;
        QString spentTimeAll;
        QString spentTimeMonth;
        QString spentTimeWeek;
    };

    QNetworkAccessManager*  mNetwrokManager{ nullptr };
    QNetworkRequest*        mNetworkRequest{ nullptr };
    QNetworkReply*          mNetworkReply{ nullptr };
    QQmlApplicationEngine*  mQmlEngine{ nullptr };
    QQmlContext*            mQmlContext{ nullptr };
    QString                 mToken;
    QList<SProjectInfo>     mProjectsInfo;
    ImageDownloader*        mImageDonwloader;


private:
    void getProjectList();
    void parseProjectsJson(QJsonDocument document);
    const QImage &downloadLogo(const QUrl &logoUrl);

signals:
    void appendNewProject(QString name,QString logo,QString spentTimeAll,QString spentTimeMonth, QString spentTimeWeek);

};

#endif // PROJECTSHANDLER_H
