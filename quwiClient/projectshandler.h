#ifndef PROJECTSHANDLER_H
#define PROJECTSHANDLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQmlContext>
#include <QMap>

#include <memory>

#include "projectmanager.h"
#include "public.h"

class ProjectsHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProjectsHandler(QObject *parent = nullptr);

public slots:
    void loadProjectsHandler();
    void appendProject(const SProjectInfo& projectInfo);
    void openSetting(QString projectName);

private:

    QQmlApplicationEngine*     mQmlEngine{ nullptr };
    QQmlContext*               mQmlContext{ nullptr };
    QString                    mToken;
    QList<SProjectInfo>        mProjectsInfo;
    QMap<QString,SProjectInfo> mProjectsMap;

signals:
    void appendNewProject(QString name,QString logo,QString spentTimeAll,QString spentTimeMonth, QString spentTimeWeek);
    void uploadProjectsList();
    void openProjectSetting(SProjectInfo selectedProject);
    void setImageSource(QString source);

};

#endif // PROJECTSHANDLER_H
