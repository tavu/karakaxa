#ifndef FOLDERMODEL_H
#define FOLDERMODEL_H

class folderModel public:QAbstractListModel
{
public:
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;

};
#endif
