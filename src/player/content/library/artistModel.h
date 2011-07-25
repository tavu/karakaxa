#ifndef ARTISTMODEL_H
#define ARTISTMODEL_H

#include<QSqlQueryModel>
#include<QSize>
#include<QStringListModel>
#include<QIcon>
#include<core.h>
class artistModel :public QStringListModel
{
    Q_OBJECT

    public:
	artistModel(QObject *parent = 0);
	QVariant data(const QModelIndex &item, int role) const;
	void updateQueries();
	void setSearch(core::queryGrt::matchQuery *qe)
	{
		q=qe;
	    _needUpdate=true;
	}
	
	void setNeedUpdate(bool t)
	{
	    _needUpdate=t;
	}
	
	bool needUpdate() const
	{
	    return _needUpdate;
	}
	
    private:

	QSize size;
	QSize itemSize;
	QPixmap artistPic;
	
	core::queryGrt::matchQuery *q;
	bool _needUpdate;
    
    public slots:    
      
	void setNeedUpdateTrue()
	{
	    _needUpdate=true;
	}
};

#endif
