#include "projectmanager.h"

ProjectManager::ProjectManager(QObject *parent):
    QObject(parent),
    mNetwrokManager( new QNetworkAccessManager(this) ),
    mNetworkRequest( new QNetworkRequest),
    mQmlEngine(new QQmlApplicationEngine(this))
{

}

ProjectManager::ProjectManager(uint64_t projectId,QString token, QObject *parent) :
    ProjectManager(parent)
{
  mToken = token;
}
