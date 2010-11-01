#ifndef FOLDERPROXYMODEL_H
#define FOLDERPROXYMODEL_H
#include<QSortFilterProxyModel>

#include"../trackUrl.h"

class folderProxyModel :public QSortFilterProxyModel , public trackUrl
{
public:
    folderProxyModel(QObject *parent=0);
    virtual KUrl url( int row) const;
};

#endif
