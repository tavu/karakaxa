#include"filemap.h"
using namespace player;
fileMap::fileMap()
{

}

void fileMap::add(const QString &path)
{
    mapItem *item=new mapItem;

//      item->path=path;
    item->tags=new fileTags(path);
    item->count=0;
    map.insert(path,item);
}

fileTags* fileMap::get(const QString &path)
{
    QMap<QString ,mapItem*>::iterator i = map.find(path);

    if (i==map.end() )
    {
        mapItem *item=new mapItem;

        item->tags=new fileTags(path);
        item->count=0;
        map.insert(path,item);
        return item->tags;
    }

    return i.value()->tags;
}
