#ifndef QUERYGENERATION_H
#define QUERYGENERATION_H
#include"../playerNamespace.h"
using namespace player;

namespace player
{
class queryGrt
{
public:
    enum equal
    {
        EQUAL=0,
        STARTS,
        ENDS,
        CONTAINS,
        GREATER,
        LESS
    };

    enum MATCH
    {
        AND=0,
        OR
    };

public:
    queryGrt();

    static QString query(tagsEnum t,equal e,QString value,bool n=false);
    static QString finish(QString);

    static QString connectAnd(QStringList l);
    static QString connectOr(QStringList l);

    static QString albums();
    static QString albums(QString artist);
    static QString albums(QString artist,QString s);

    static QString tracks(int albumId);
    static QString tracks(int albumId,QString s);
    static QString tracks(QString s);
    static QString tracks();

private:
    static QString tagToSql(tagsEnum t);

};
};
#endif
