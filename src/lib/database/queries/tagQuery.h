#ifndef TAGQUERY_H
#define TAGQUERY_H

#include"abstractQuery.h"
#include"queryTypes.h"

namespace database
{

    class tagQuery :public abstractQuery
    {
        public:
            tagQuery(QObject *parent=0);
            tagQuery(int t,equal e,QVariant var,bool n=false,QObject *parent=0);
            tagQuery(tagQuery *t,QObject *parent=0);


            short int type() const
            {
                return TAGQ;
            }

            bool isValid() const
            {
                return valid;
            }

            bool isReverted() const
            {
                return revert;
            }

            void setRevert(bool r)
            {
                revert=r;
            }

            abstractQuery * clone()
            {
                return new tagQuery(this);
            }

            void init(int t,equal e,QVariant var,bool n=false) const;
            bool match(const audioFiles::audioFile &f) const;
            QString text(QString table=QString() ) const;
            
            QList<int> tags() const;

        private:
            mutable bool valid;
            int tag;
            equal eq;
            QVariant value;
            bool revert;
            mutable QString q;
    };
    
}

#endif