#include "projectmanager.h"

ProjectManager::ProjectManager(QObject *parent):
    QObject(parent),
    mNetwrokManager( new QNetworkAccessManager(this) ),
    mNetworkRequest( new QNetworkRequest),
    mQmlEngine(new QQmlApplicationEngine(this))
{

}

void ProjectManager::changeName(const QString &newName)
{
    QString headerData = "Bearer ";
    headerData.append(mToken);
                    QString url = "https://api.quwi.com/v2/projects-manage/update?id=";
                    url.append(QString::number(mProjectInfo.projectId));
    mNetworkRequest->setUrl(QUrl(url));

    mNetworkRequest->setRawHeader("Authorization", headerData.toLocal8Bit() );
    mNetworkRequest->setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString data = "name=";
    data.append(newName);

    qDebug() << mNetworkRequest->rawHeaderList();
    mNetwrokManager->put(*mNetworkRequest,data.toLocal8Bit());
}

ProjectManager::ProjectManager(const SProjectInfo& projectInfo,QString token, QObject *parent) :
    ProjectManager(parent)
{
  mToken = token;
  mProjectInfo = projectInfo;
  const QUrl url(QStringLiteral("qrc:/projectSetting.qml"));
  mQmlContext = mQmlEngine->rootContext();
  mQmlContext->setContextProperty("projectSetting",this);

  QObject::connect(mQmlEngine, &QQmlApplicationEngine::objectCreated,
                   this, [this,url](QObject *obj, const QUrl &objUrl) {

  }, Qt::QueuedConnection);

  mQmlEngine->load(url);
  auto isActiveSwitch = mQmlEngine->rootObjects().first()->findChild<QObject*>("activeSwithObject");
  if( isActiveSwitch )
  {
    isActiveSwitch->setProperty("checked", projectInfo.isActive ? " true" : "false");
  }
  auto ownerWatchedSwitch = mQmlEngine->rootObjects().first()->findChild<QObject*>("ownerWatchedSwitch");
  if( ownerWatchedSwitch )
  {
    ownerWatchedSwitch->setProperty("checked", projectInfo.isOwnerWatcher ? " true" : "false");
  }
   auto projectNameEdit = mQmlEngine->rootObjects().first()->findChild<QObject*>("projectNameEdit");
   if( projectNameEdit )
   {
      projectNameEdit->setProperty("text", projectInfo.name);
   }


}
