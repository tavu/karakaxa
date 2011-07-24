#ifndef CORE_FUNC_H
#define CORE_FUNC_H

#include<QString>
#include<QVariant>
#include<QUrl>

namespace core
{
  
QString 	folder(QString path) ;
QString 	titleFromPath(const QString &path);
bool   		isStream(const QString s);
bool   		isStream(const QUrl url);
bool 		isDirectory(const QString &url);
bool		isPlaylist(const QString &url);
bool 		isAudio(const QString &url);
bool		isImage(const QString &url);

QString 	format(QString path);

// void 		editTrack(const QString &s);
void 		init();
void 		cleanUp();
bool		exists(const QString &url);
QThread*	mainThr();

int getRandomN(int min,int max);


template <class RandomAccessIterator>
void randomShuffle ( RandomAccessIterator first, int size )
{
      RandomAccessIterator it,tmp;
      it=first;
      for(int i=0;i<size;i++)
      {	  	  
	  int r=getRandomN(0,size-1);
	  tmp=first+r;
 	  qSwap(*it,*tmp );
	  it++;
      }
	
} 


};
#endif