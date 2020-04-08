#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQmlContext>

#include "public.h"

class ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(QObject *parent = nullptr);

public slots:

    void openProjectSetting(SProjectInfo selectedProject);
    void changeProjectName(QString newName);
private:
    std::unique_ptr<QQmlApplicationEngine>  mQmlEngine{ nullptr };
    QQmlContext*                            mQmlContext{ nullptr };
    SProjectInfo                            mProjectInfo;

signals:
    void setImageSource(QString source);
    void changeProjectSetting(const SProjectInfo& newName);
};

#endif // PROJECTMANAGER_H
