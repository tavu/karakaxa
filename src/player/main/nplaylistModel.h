#ifndef NPLMODEL_H
#define NPLMODEL_H

#include<models/playlistModel.h>
#include <set>

using namespace core;
// using namespace views;
// #include<QList>
// #include<nplaylist.h>

// extern nplaylist npList;

class nplModel :public views::playlistModel
{
    Q_OBJECT
    public:
        nplModel( QObject * parent = 0);
        ~nplModel()
        {
            pl=0;
        }
        bool dropMimeData (const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

//         void clearReorder();
//         void setReorder(set<int> &l);
//         void reorder(int r,const std::set<int> &rows);
};
#endif
