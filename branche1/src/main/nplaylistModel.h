#ifndef NPLMODEL_H
#define NPLMODEL_H

#include<QAbstractItemModel>
#include<player.h>
// #include<QList>
// #include<nplaylist.h>

// extern nplaylist npList;

class nplModel :public QAbstractListModel
{
    Q_OBJECT
    public:
	nplModel( QObject * parent = 0);

	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	bool dropMimeData (const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	Qt::DropActions supportedDropActions () const;
	QStringList mimeTypes () const;
	Qt::ItemFlags flags(const QModelIndex &index) const;


	void clearReorder();
	void setReorder(QList<int> &l);
	void reorder(int);

    private:
    // 	  QList <int> rows;
	QAbstractItemView *view;
	QList<int> reorderL;
	int size;

    private slots:
	void beginInsert(int pos);
	void beginRemove(int);
	void beginClear(int);
	void end(int);



};
#endif
