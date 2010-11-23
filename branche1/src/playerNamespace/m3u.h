#ifndef M3UP_H
#define M3UP_H

#include <QFile>
#include <kurl.h>
#include<QString>
#include<iostream>
#include<playerNamespace.h>
namespace player
{
class m3uPl
{
public:
    m3uPl(QString s);

    QList<QString> urls() const;

    inline QString item(int row)
    {
        if (row>=list.size() )
        {
            return QString();
        }
        else
        {
            return list.at(row);
        }
    }

    inline void insert(int row,QString u)
    {
        if (row>=list.size() )
        {
            list.prepend(u);
        }
        else
        {
            list.insert(row,u);
        }
    }

    inline void move( int from, int to )
    {
        if (from>=list.size() ||  to>=list.size())
        {
            return ;
        }
        else
        {
            list.move(from,to);
        }
    }

    inline void remove(int row)
    {
        if (row>=list.size() )
        {
            return ;
        }
        list.removeAt(row);
    }

    inline int size()
    {
        return list.size();
    }

    QString getError() const;


    inline QString folder()
    {
        return player::folder(path);
    }

    void load();
private:

    void save();
    void toLocal(QString &s);
    QString path;
    QFile file;
    QString error;
    QList<QString> list;

};
};
#endif
