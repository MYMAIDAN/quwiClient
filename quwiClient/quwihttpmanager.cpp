#include "quwihttpmanager.h"
#include "public.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QImage>
#include <QUrl>
#include <QFileInfo>
#include <QCoreApplication>
#include <QResource>

QuwiHttpManager::QuwiHttpManager(QObject *parent) :
    QObject(parent),
    mNetworkManager(std::make_unique<QNetworkAccessManager>(this)),
    mNetworkRequest(std::make_unique<QNetworkRequest>())
{

}

void QuwiHttpManager::authorization(const QString &email, const QString &password)
{
  mNetworkRequest->setUrl(QUrl("https://api.quwi.com/v2/auth/login"));
  mNetworkRequest->setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,"application/json");
  QVariantMap parameter;
  parameter["email"] =  email;
  parameter["password"] = password;
  mNetworkReply.reset(mNetworkManager->post(*mNetworkRequest,QJsonDocument::fromVariant(parameter).toJson()));
  connect(mNetworkReply.get(),&QNetworkReply::finished,this,&QuwiHttpManager::authorizationRequest);
}

void QuwiHttpManager::uploadProjectsList()
{
  mNetworkRequest->setUrl(QUrl("https://api.quwi.com/v2/projects-manage/index"));
  mNetworkReply.reset(mNetworkManager->get(*mNetworkRequest));
  connect(mNetworkReply.get(),&QNetworkReply::finished,this,&QuwiHttpManager::projectListRecieved);
}

void QuwiHttpManager::authorizationRequest()
{
    if( mNetworkReply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt() == 417 )
    {
        emit authorizationRequestFinished(EAuthorizationStatus::eAuthorizationError);
    }
    if( mNetworkReply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt() == 200 )
    {
        QJsonDocument item = QJsonDocument::fromJson(mNetworkReply->readAll());
        QJsonObject object = item.object();
        QString headerData = "Bearer ";
        headerData.append(object.value("token").toString());
        mNetworkRequest->setRawHeader("Authorization", headerData.toLocal8Bit() );
        emit authorizationRequestFinished(EAuthorizationStatus::eOK);
    }
}

void QuwiHttpManager::projectListRecieved()
{

    QJsonDocument document = QJsonDocument::fromJson(mNetworkReply->readAll());
        auto object  = document.object();
        auto array = object.value("projects");
        auto arrayIt  = array.toArray();
        SProjectInfo projectInfo;
        for( auto it: arrayIt)
        {
            auto project                 = it.toObject();
            projectInfo.name             = project.value("name").toString();
            projectInfo.spentTimeAll     = project.value("spent_time_all").toString();
            projectInfo.spentTimeMonth   = project.value("spent_time_month").toString();
            projectInfo.spentTimeWeek    = project.value("spent_time_week").toString();
            projectInfo.projectId        = project.value("id").toInt();
            projectInfo.isActive         = project.value("is_active").toInt();
            projectInfo.isOwnerWatcher   = project.value("is_owner_watcher").toInt();

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
            if( project.value("logo_url").toString() == "Null")
            {
                emit this->appendProject(projectInfo);
                return;
            }
            mNetworkRequest->setUrl(QUrl(project.value("logo_url").toString()));
            mImageReply.push_back(mNetworkManager->get(*mNetworkRequest));
            QNetworkReply *value = mImageReply.back();
            connect(mImageReply.back(),&QNetworkReply::finished,this,[this,value,projectInfo](){

                QImage image = QImage::fromData(value->readAll());
                QString path = QCoreApplication::applicationDirPath() + "/Project " + projectInfo.name + ".png";
                QFileInfo finfo(path);

                QResource::registerResource(path);
                image.save(path);
                SProjectInfo info = projectInfo;
                info.logoUrl = path;
                emit this->appendProject(info);

            });
        }
}


