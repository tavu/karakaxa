#ifndef NPLMODEL_H
#define NPLMODEL_H

#include<QAbstractItemModel>
#include<nowPlayList/nplAbstractModel.h>
#include<QAbstractItemView>
// #include<nplAbstractModel.h>
#include <set>
using namespace std;
using namespace core;
// using namespace views;
// #include<QList>
// #include<nplaylist.h>

// extern nplaylist npList;

class nplModel :public nplAbstractModel
{
    Q_OBJECT
    public:
        nplModel( QObject * parent = 0);

        QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
        bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
        int columnCount ( const QModelIndex & parent = QModelIndex() ) const ;
        bool dropMimeData (const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
        Qt::DropActions supportedDropActions () const;
        QStringList mimeTypes () const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

        void clearReorder();
        void setReorder(set<int> &l);
        void reorder(int);

    private:
    // 	  QList <int> rows;
	//QAbstractItemView *view;
	//set<int> reorderL;
        int size;



};
#endif
