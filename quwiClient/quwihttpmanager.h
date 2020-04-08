#ifndef QUWIHTTPMANAGER_H
#define QUWIHTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <memory>
#include "public.h"
#include <QList>


class QuwiHttpManager : public QObject
{
    Q_OBJECT
public:
    explicit QuwiHttpManager(QObject *parent = nullptr);

signals:
    void authorizationRequestFinished(EAuthorizationStatus status);
    void appendProject(const SProjectInfo& projectInfo);
    void setImageSource(QString source);

public slots:
    void authorization(const QString& email, const QString& password);
    void uploadProjectsList();
    void changeProjectSetting(const SProjectInfo& projectSetting);

private:
    std::unique_ptr<QNetworkAccessManager> mNetworkManager;
    std::unique_ptr<QNetworkRequest>       mNetworkRequest;
    std::unique_ptr<QNetworkReply>         mNetworkReply;
    QList<QNetworkReply*>                  mImageReply;

private slots:
    void authorizationRequest();
    void projectListRecieved();
};

#endif // QUWIHTTPMANAGER_H
