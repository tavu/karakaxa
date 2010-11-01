#ifndef FILEPMAP_H
#define FILEPMAP_H
#include<QString>
#include<QMap>
#include<player.h>
using namespace player;

struct fileMapItem
{
//      QString 	path;
    int 	count;
    fileTags 	*tags;
};
typedef  struct fileMapItem mapItem;


class fileMap
{
public:
    fileMap();

    fileTags* get(const QString &path);
    void add(const QString &path);
private:
    QMap<QString, mapItem*> map;

};

#endif
