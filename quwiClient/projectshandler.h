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
#include <QMap>

#include "imagedownloader.h"
#include "projectmanager.h"
#include "public.h"

class ProjectsHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProjectsHandler(QObject *parent = nullptr);



public slots:
    void loadProjectsHandler();
    void openProjectSetting(QString projectName);
    void appendProject(const SProjectInfo& projectInfo);


private:

    QNetworkAccessManager*  mNetwrokManager{ nullptr };
    QNetworkRequest*        mNetworkRequest{ nullptr };
    QNetworkReply*          mNetworkReply{ nullptr };
    QQmlApplicationEngine*  mQmlEngine{ nullptr };
    QQmlContext*            mQmlContext{ nullptr };
    QString                 mToken;
    QList<SProjectInfo>     mProjectsInfo;
    ImageDownloader*        mImageDonwloader;
    ProjectManager*         mProjectManager;
    QMap<QString,SProjectInfo>* mProjectsMap;


private:
    void getProjectList();
    void parseProjectsJson(QJsonDocument document);
    const QImage &downloadLogo(const QUrl &logoUrl);

signals:
    void appendNewProject(QString name,QString logo,QString spentTimeAll,QString spentTimeMonth, QString spentTimeWeek);
    void uploadProjectsList();

};

#endif // PROJECTSHANDLER_H
