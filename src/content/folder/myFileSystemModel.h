#ifndef MYFILESYSTEMMODEL_H
#define MYFILESYSTEMMODEL_H
#include<KDirModel>
#include <QFileSystemModel>
#include<KDirLister>
#include<player.h>
#include"../trackUrl.h"
#define DIRCOLUMN 7
using namespace player;
class myFileSystemModel :public KDirModel , public trackUrl
{
    Q_OBJECT
public:
    myFileSystemModel(QObject *parent=0);
    int columnCount( const QModelIndex & parent ) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const ;
    void updateTrack(audioFile *f);
    int infoC();

    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    virtual KUrl url( int row) const;

private:

    KDirLister *dirL;
    QList<QString> fileList;

private slots:
    void insert(const KFileItemList &items);
    void cleanup();

    
  signals:
    void updated();
};
#endif
