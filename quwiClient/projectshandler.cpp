#include "projectshandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ProjectsHandler::ProjectsHandler(QObject *parent) :
    QObject(parent),
    mNetwrokManager( new QNetworkAccessManager(this) ),
    mNetworkRequest( new QNetworkRequest),
    mQmlEngine(new QQmlApplicationEngine(this))
{


}

void ProjectsHandler::loadProjectsHandler(QString token)
{
    const QUrl url(QStringLiteral("qrc:/projectsView.qml"));
    mQmlContext = mQmlEngine->rootContext();

    QObject::connect(mQmlEngine, &QQmlApplicationEngine::objectCreated,
                     this, [url](QObject *obj, const QUrl &objUrl) {
    }, Qt::QueuedConnection);

    QObject::connect(mNetwrokManager,&QNetworkAccessManager::finished,this,[this](QNetworkReply* reply){
        parseProjectsJson(QJsonDocument::fromJson(reply->readAll()));
    });
    mQmlEngine->load(url);
    mToken = token;
    getProjectList();
}

void ProjectsHandler::getProjectList()
{
    QString headerData = "Bearer ";
    headerData.append(mToken);
    mNetworkRequest->setUrl(QUrl("https://api.quwi.com/v2/projects-manage/index"));
    mNetworkRequest->setRawHeader("Authorization", headerData.toLocal8Bit() );
   // mNetworkRequest->setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW");
    qDebug() << mNetworkRequest->rawHeaderList();
    mNetwrokManager->get(*mNetworkRequest);

}

void ProjectsHandler::parseProjectsJson(QJsonDocument document)
{
    auto object  = document.object();
    auto array = object.value("projects");
    auto arrayIt  = array.toArray();
    SProjectInfo projectInfo;
    for( auto it: arrayIt)
    {
        auto project =  it.toObject();
        projectInfo.name = project.value("name").toString();
        projectInfo.logoUrl = project.value("logo_url").toString();
        projectInfo.spentTimeAll = project.value("spent_time_all").toString();
        projectInfo.spentTimeMonth = project.value("spent_time_month").toString();
        projectInfo.spentTimeWeek = project.value("spent_time_week").toString();
        mProjectsInfo.push_back(projectInfo);

    }

}

const QImage &ProjectsHandler::downloadLogo(const QUrl &logoUrl)
{
    mNetworkRequest->setUrl(logoUrl);
}
