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
	void setSearch(core::queryGrt::abstractQuery *qe)
	{
// 	    q=qe;
	    if(qe->isValid())
	    {
		artistQ->setQuery(qe->clone());
	    }
	    else
	    {
		artistQ->setQuery(0);
	    }
// 	    _needUpdate=true;
	}
	
	void setNeedUpdate(bool t)
	{
	    _needUpdate=t;
	}
	
	bool needUpdate() const
	{
	    return _needUpdate;
	}
	
	const core::artistQueryGrt * queryGrt()
	{
	    return artistQ;
	}
	
    private:

	QSize size;
	QSize itemSize;
	QPixmap artistPic;
	
	core::queryGrt::abstractQuery *q;
	core::artistQueryGrt *artistQ;
	bool _needUpdate;
	
    
    public slots:    
      
	void setNeedUpdateTrue()
	{
	    _needUpdate=true;
	}
};

#endif
