#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include<QString>
#include<QVariant>
#include<QUrl>

namespace Basic
{

QString         folder(QString path) ;
QString 	titleFromPath(const QString &path);
bool            isStream(const QString s);
bool            isStream(const QUrl url);
bool 		isDirectory(const QString &url);
bool		isPlaylist(const QString &url);
bool            isAudio(const QString &url);
bool		isImage(const QString &url);
bool            removeDir(const QString &dirName);
QString         format(QString path);
void 	    	init();
void            cleanUp();
bool            exists(const QString &url);

int             getRandomN(int min,int max);
void            karakaxaMsg(QtMsgType type, const char *msg);

template <class RandomAccessIterator>
void randomShuffle ( RandomAccessIterator first, int size )
{
    RandomAccessIterator it,tmp;
    it=first;
    for(int i=0; i<size; i++)
    {
        int r=getRandomN(0,size-1);
        tmp=first+r;
        qSwap(*it,*tmp );
        it++;
    }

}

};
#endif