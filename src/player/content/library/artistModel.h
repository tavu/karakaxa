#ifndef ARTISTMODEL_H
#define ARTISTMODEL_H

#include<QSqlQueryModel>
#include<QSize>
#include<QSqlQuery>
#include<QIcon>
class artistModel :public QSqlQueryModel
{
    Q_OBJECT

public:
    artistModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;

private:

    QSize size;
    QSize itemSize;
    QPixmap artistPic;
        
};

#endif
