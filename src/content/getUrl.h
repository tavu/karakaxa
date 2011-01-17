#ifndef TRACKURL_H
#define TRACKURL_H

#include <QLinkedList>
#include<KUrl>
class trackUrl
{
public:
    virtual KUrl url(int row)=0;
    
    //when we create an editor from the myTreeView class we append the url of the selected indexes to itemList.
    //This make posible to edit all the selected items, not just the index of the editor
    //if u don't want that ignore that list    
    QLinkedList<KUrl> urlList;
};
#endif
