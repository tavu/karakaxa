#ifndef SONGMODEL_H
#define SONGMODEL_H

#include <QSqlTableModel>

#include<trackUrl.h>

// #include<QWidget>
#include<player.h>
#include<trackView.h>

class songModel :public QSqlTableModel ,public trackUrl
{
    Q_OBJECT

public:
    songModel(QWidget *parent );
    QVariant data(const QModelIndex &item, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    virtual KUrl url( int row) const;
    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
private:

// 	  QSqlQueryModel queryM;

public slots:
    void refresh();

};


#endif
