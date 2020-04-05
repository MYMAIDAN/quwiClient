#include "imagedownloader.h"

ImageDownloader::ImageDownloader(QObject *parent) :
    QObject(parent),
    mNetwrokManager( new QNetworkAccessManager(this) ),
    mNetworkRequest( new QNetworkRequest)
{

    connect(mNetwrokManager,&QNetworkAccessManager::finished,this,[](QNetworkReply* reply){
                qDebug() << "Finished";

                static uint16_t projectsNumber{ 0 };
                QImage image = QImage::fromData(reply->readAll());
                QString path = "Project " + QString::number(projectsNumber) + ".png";

                image.save(path);
            });

}

ImageDownloader::ImageDownloader(QString token, QObject *parent) :
    ImageDownloader(parent)
{
    mToken = token;
    QString headerData = "Bearer ";
    headerData.append(mToken);
    mNetworkRequest->setRawHeader("Authorization", headerData.toLocal8Bit() );
}

const QUrl &ImageDownloader::downloadImage(const QUrl &imageUrl)
{

    mNetworkRequest->setUrl(imageUrl);
    qDebug() << mNetworkRequest->rawHeaderList();
    auto reply = mNetwrokManager->get(*mNetworkRequest);
    return imageUrl;
}
