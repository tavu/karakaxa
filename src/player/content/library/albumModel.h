#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include<QSqlQueryModel>
#include<QSize>
#include<QSqlQuery>
#include<QIcon>
#include<QSqlRecord>
#include<QVariant>

class albumModel :public QSqlQueryModel
{
    Q_OBJECT

public:
    albumModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;
    ~albumModel();
    int albumId(const int row);
    void resize(QSize &s);
private:

    QSize itemSize;
    QSize maxSize;
    QSize minSize;
    QSize imageSize;
    QIcon *artistIcon;
    QIcon *songIcon;
    QIcon *albumIcon;
    
    
    QPixmap *pix;
    QPixmap *defaultPic;

    void queryChange ();
    void resizePix();
};

#endif