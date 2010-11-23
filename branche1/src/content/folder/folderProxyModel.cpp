#include"folderProxyModel.h"

folderProxyModel::folderProxyModel(QObject *parent)
        :QSortFilterProxyModel(parent)
{
}

KUrl folderProxyModel::url( int row) const
{
    trackUrl *t=dynamic_cast<trackUrl*> (sourceModel() );

    if (t==0)	return KUrl();
    QModelIndex i=mapToSource(index(row,0) );
    return t->url(i.row());

}
