#include "projectshandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>

ProjectsHandler::ProjectsHandler(QObject *parent) :
    QObject(parent),
    mQmlEngine(new QQmlApplicationEngine(this))
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


void ProjectsHandler::appendProject(const SProjectInfo &projectInfo)
{
    mProjectsMap.insert(projectInfo.name,projectInfo);
    emit appendNewProject(projectInfo.name,
                          projectInfo.logoUrl,
                          projectInfo.spentTimeAll,
                          projectInfo.spentTimeMonth,
                          projectInfo.spentTimeWeek
                          );
}

void ProjectsHandler::openSetting(QString projectName)
{
    emit openProjectSetting(mProjectsMap.find(projectName).value());
}
