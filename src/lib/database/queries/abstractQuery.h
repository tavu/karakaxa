#ifndef ABSTRACTQUERY_H
#define ABSTRACTQUERY_H

#include<audioFile.h>
#include<QObject>

namespace database
{
    class abstractQuery :public QObject
    {

        public:
            abstractQuery(QObject *parent=0) :QObject(parent){};
            virtual ~abstractQuery(){};
            
            virtual QString text() const =0;
            virtual short int type() const =0;
            virtual bool isValid() const =0;
            virtual bool match(const audioFiles::audioFile &f) const =0;
            virtual abstractQuery * clone()=0;


//         protected:
            static QString tagToSql(int t);
    }; 
}
#endif