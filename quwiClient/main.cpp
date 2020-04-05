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

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    ProjectsHandler projectsHandler;

    Login login;
    QObject::connect(&login,&Login::successLogin,&projectsHandler,&ProjectsHandler::loadProjectsHandler);

    return app.exec();
}
