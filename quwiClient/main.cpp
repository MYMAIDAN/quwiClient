#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QVariantMap>
#include <QJsonDocument>

#include "login.h"
#include "projectshandler.h"
#include "quwihttpmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    ProjectsHandler projectsHandler;
    QuwiHttpManager quwiManager;

    Login login;

    QObject::connect(&login,&Login::authorization,&quwiManager,&QuwiHttpManager::authorization);
    QObject::connect(&quwiManager,&QuwiHttpManager::authorizationRequestFinished,&login,&Login::authorizationRequestFinished);

    QObject::connect(&login,&Login::authorizationSuccess,&projectsHandler, &ProjectsHandler::loadProjectsHandler);

    QObject::connect(&projectsHandler,&ProjectsHandler::uploadProjectsList,&quwiManager,&QuwiHttpManager::uploadProjectsList);
    QObject::connect(&quwiManager,&QuwiHttpManager::appendProject,&projectsHandler,&ProjectsHandler::appendProject);

    return app.exec();
}
