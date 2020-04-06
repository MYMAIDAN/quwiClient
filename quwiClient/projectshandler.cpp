#include "projectshandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ProjectsHandler::ProjectsHandler(QObject *parent) :
    QObject(parent),
    mNetwrokManager( new QNetworkAccessManager(this) ),
    mNetworkRequest( new QNetworkRequest),
    mQmlEngine(new QQmlApplicationEngine(this)),
    mProjectsMap(new QMap<QString,SProjectInfo>)
{


}

void ProjectsHandler::loadProjectsHandler(QString token)
{
    const QUrl url(QStringLiteral("qrc:/projectsView.qml"));
    mQmlContext = mQmlEngine->rootContext();
    mQmlContext->setContextProperty("newProjectHandler",this);

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

void ProjectsHandler::openProjectSetting(QString projectName)
{
    if( mProjectManager != nullptr)
    {
        delete mProjectManager;
    }
    auto it  = mProjectsMap->find(projectName);
    if( it != mProjectsMap->end() )
    {
        mProjectManager = new ProjectManager(it.value(),mToken);
    }

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
    mImageDonwloader  = new ImageDownloader(mToken);
    for( auto it: arrayIt)
    {
        auto project =  it.toObject();
        projectInfo.name = project.value("name").toString();
        if( project.value("logo_url").isNull()){
           projectInfo.logoUrl = "null";
        }
        else
        {
            mImageDonwloader->downloadImage(QUrl(project.value("logo_url").toString()));
        }

        projectInfo.spentTimeAll = project.value("spent_time_all").toString();
        projectInfo.spentTimeMonth = project.value("spent_time_month").toString();
        projectInfo.spentTimeWeek = project.value("spent_time_week").toString();
        projectInfo.projectId     = project.value("id").toInt();
        projectInfo.isActive = project.value("is_active").toInt();
        projectInfo.isOwnerWatcher = project.value("is_owner_watcher").toInt();
        mProjectsInfo.push_back(projectInfo);

        if(projectInfo.spentTimeAll.isEmpty())
        {
            projectInfo.spentTimeAll = "00:00:00";
        }
        if(projectInfo.spentTimeMonth.isEmpty())
        {
            projectInfo.spentTimeMonth = "00:00:00";
        }
        if(projectInfo.spentTimeWeek.isEmpty())
        {
            projectInfo.spentTimeWeek = "00:00:00";
        }

        mProjectsMap->insert(projectInfo.name,projectInfo);
        emit appendNewProject(projectInfo.name,
                              projectInfo.logoUrl.toString(),
                              projectInfo.spentTimeAll,
                              projectInfo.spentTimeMonth,
                              projectInfo.spentTimeWeek);

    }

}

const QImage &ProjectsHandler::downloadLogo(const QUrl &logoUrl)
{
    QImage image;
    mNetworkRequest->setUrl(logoUrl);
}
