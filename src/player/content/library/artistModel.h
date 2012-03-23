#ifndef ARTISTMODEL_H
#define ARTISTMODEL_H

#include<QSqlQueryModel>
#include<QSize>
#include<QStringListModel>
#include<QIcon>
#include<core.h>
#include<queries/abstractQuery.h>
#include<queries/artistQueryGrt.h>
class artistModel :public QStringListModel
{
    Q_OBJECT

    public:
        artistModel(QObject *parent = 0);
        
        QVariant data(const QModelIndex &item, int role) const;
        void updateQueries();
        void setSearch(database::abstractQuery *qe)
        {
            if(qe->isValid())
            {
                artistQ->setQuery(qe->clone());
            }
            else
            {
                artistQ->setQuery(0);
            }    
        }

        void setNeedUpdate(bool t)
        {
            _needUpdate=t;
        }

        bool needUpdate() const
        {
            return _needUpdate;
        }

        const database::artistQueryGrt * queryGrt()
        {
            return artistQ;
        }
	
    private:

        QSize size;
        QSize itemSize;
        QPixmap artistPic;

        database::abstractQuery *q;
        database::artistQueryGrt *artistQ;
        bool _needUpdate;


    public slots:    
      
        void setNeedUpdateTrue()
        {
            _needUpdate=true;
        }
};

#endif
