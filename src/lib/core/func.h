#ifndef CORE_FUNC_H
#define CORE_FUNC_H

#include<QString>
#include<QVariant>
#include<QUrl>
#include <QSizePolicy>
#include<QWidget>
#include<Basic/func.h>
namespace core
{
void init();
template <class RandomAccessIterator>
void randomShuffle ( RandomAccessIterator first, int size )
{
    RandomAccessIterator it,tmp;
    it=first;
    for(int i=0; i<size; i++)
    {
        int r=Basic::getRandomN(0,size-1);
        tmp=first+r;
        qSwap(*it,*tmp );
        it++;
    }

}


};
#endif