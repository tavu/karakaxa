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

            void init(int t,equal e,QVariant var,bool n=false);
            bool match(const audioFiles::audioFile &f) const;
            QString text() const;

        private:
            bool valid;
            int tag;
            equal eq;
            QVariant value;
            bool revert;
            QString q;
    };
    
}

#endif