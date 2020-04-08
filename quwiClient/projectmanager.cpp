#include "projectmanager.h"

ProjectManager::ProjectManager(QObject *parent):
    QObject(parent)
{

}

void ProjectManager::openProjectSetting(SProjectInfo selectedProject)
{

    mProjectInfo = selectedProject;
        mQmlEngine = std::make_unique<QQmlApplicationEngine>(this);
    const QUrl url(QStringLiteral("qrc:/projectSetting.qml"));
    mQmlContext = mQmlEngine->rootContext();
    mQmlContext->setContextProperty("projectSetting",this);

    QObject::connect(mQmlEngine.get(), &QQmlApplicationEngine::objectCreated,
                     this, [this,url](QObject *obj, const QUrl &objUrl) {

    }, Qt::QueuedConnection);

    mQmlEngine->load(url);
    auto isActiveSwitch = mQmlEngine->rootObjects().first()->findChild<QObject*>("activeSwithObject");
    if( isActiveSwitch )
    {
      isActiveSwitch->setProperty("checked", mProjectInfo.isActive ? " true" : "false");
    }
    auto ownerWatchedSwitch = mQmlEngine->rootObjects().first()->findChild<QObject*>("ownerWatchedSwitch");
    if( ownerWatchedSwitch )
    {
      ownerWatchedSwitch->setProperty("checked", mProjectInfo.isOwnerWatcher ? " true" : "false");
    }
     auto projectNameEdit = mQmlEngine->rootObjects().first()->findChild<QObject*>("projectNameEdit");
     if( projectNameEdit )
     {
        projectNameEdit->setProperty("text", mProjectInfo.name);
     }
     auto logoImage = mQmlEngine->rootObjects().first()->findChild<QObject*>("logoImage");
     if( logoImage )
     {
        emit setImageSource(mProjectInfo.logoUrl);
     }
}

void ProjectManager::changeProjectName(QString newName)
{
    mProjectInfo.name = newName;
    emit changeProjectSetting(mProjectInfo);
}

