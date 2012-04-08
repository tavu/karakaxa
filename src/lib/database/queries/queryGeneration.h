#ifndef QUERYGENERATION_H
#define QUERYGENERATION_H

#include<QString>
#include<QVector>
#include<QDebug>

#include<audioFile.h>

#include"../album.h"
#include"abstractQuery.h"
#include"queryThr.h"
#include"../dbBase.h"
#include"databaseEvent.h"

namespace database
{


class queryGrt :public dbBase
{
    Q_OBJECT
    public:    
        queryGrt(QObject *parent=0);
        queryGrt(abstractQuery* qe,QObject *parent=0);

        QString filter() const
        {
            if (q==0)
            {
                return QString();
            }
            return q->text();
        }

        const abstractQuery* query() const
        {
            return q;
        }

        void setQuery(abstractQuery *qe)
        {
            if (q!=0)
            {
                delete q;
            }
            q=qe;
            _needUpdate=true;
        }

        virtual QString queryString() const=0;
        virtual bool select()=0;

        bool needUpdate() const
        {
            return _needUpdate;
        }


    protected:       
        
        abstractQuery *q;
        bool _needUpdate;

    protected slots:
        void setNeedUpdate();
        virtual void dbEvents(database::dbEventP e);
        
    signals:
        void updateNeeded();

};

};
#endif
