#include"random.h"
#include<cstdlib>
#include<QDebug>
inline int getRandomN(int min,int max)
{
    return  qrand()/ (RAND_MAX + 1.0) * (max + 1 - min) + min ;
}

template <class RandomAccessIterator>
void randomShuffle ( RandomAccessIterator first, int size ) 
{
      qDebug()<<"edoeep"<<size;
      RandomAccessIterator it,tmp;
      it=first;
//       iterator_traits<RandomAccessIterator>::difference_type i, n;
      for(int i=0;i<size;i++)
      {	  	  
	  int r=getRandomN(0,size-1);
	  qDebug()<<r;
	  tmp=first+r;
// 	  qDebug()<<*(tmp+3);
// 	  qDebug()<<*it;
	  
	  
// 	  *it=first[r];
 	  qSwap(*it,*tmp );
	  it++;
      }
	
} 