#ifndef MACHQUERY
#define MACHQUERY

#include<QList>

#include"abstractQuery.h"
#include"queryTypes.h"

namespace database
{
    enum MATCH
    {
        AND=0,
        OR
    };


    class matchQuery :public abstractQuery
    {

        public:
            matchQuery(MATCH m,QObject *parent=0);
            ~matchQuery();
            matchQuery(matchQuery *mq,QObject *parent=0);

            short int type() const
            {
                return MATCHQ;
            }

            bool isValid() const;
            QString text() const;
            bool append(abstractQuery *q);

            bool match(const audioFiles::audioFile &f) const;
            abstractQuery * clone()
            {
                return new matchQuery(this);
            }

            void clear();

        private:
            bool valid;
            MATCH matchType;
            QList<abstractQuery*> queries;
            QString q;
    };    
};


#endif