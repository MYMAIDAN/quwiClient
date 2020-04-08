#include "projectshandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>

ProjectsHandler::ProjectsHandler(QObject *parent) :
    QObject(parent),
    mNetwrokManager( new QNetworkAccessManager(this) ),
    mNetworkRequest( new QNetworkRequest),
    mQmlEngine(new QQmlApplicationEngine(this)),
    mProjectsMap(new QMap<QString,SProjectInfo>)
{


}

void ProjectsHandler::loadProjectsHandler()
{
    const QUrl url(QStringLiteral("qrc:/projectsView.qml"));
    emit uploadProjectsList();
    mQmlContext = mQmlEngine->rootContext();
    mQmlContext->setContextProperty("newProjectHandler",this);

    QObject::connect(mQmlEngine, &QQmlApplicationEngine::objectCreated,
                     this, [url](QObject *obj, const QUrl &objUrl) {
    }, Qt::QueuedConnection);

    mQmlEngine->load(url);
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

void ProjectsHandler::appendProject(const SProjectInfo &projectInfo)
{
    emit appendNewProject(projectInfo.name,
                          projectInfo.logoUrl,
                          projectInfo.spentTimeAll,
                          projectInfo.spentTimeMonth,
                          projectInfo.spentTimeWeek
                          );
}
