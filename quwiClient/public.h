#ifndef PUBLIC_H
#define PUBLIC_H


struct SProjectInfo
{
    int     projectId;
    QString name;
    QUrl    logoUrl;
    QString spentTimeAll;
    QString spentTimeMonth;
    QString spentTimeWeek;
    bool    isActive;
    bool    isOwnerWatcher;
};


#endif // PUBLIC_H
