#ifndef PUBLIC_H
#define PUBLIC_H


struct SProjectInfo
{
    int     projectId;
    QString name;
    QString logoUrl;
    QString spentTimeAll;
    QString spentTimeMonth;
    QString spentTimeWeek;
    bool    isActive;
    bool    isOwnerWatcher;
};

enum EAuthorizationStatus
{
    eOK = 0,
    eAuthorizationError
};


#endif // PUBLIC_H
