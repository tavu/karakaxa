#ifndef NPLTREAD_H
#define NPLTREAD_H

#include<QThread>
#include<QUrl>
// #include<nplaylist.h>
// #include<player.h>
#include<playerNamespace.h>
#include<QProgressBar>
//this class have the porpose of finding the file info and appending the now playlist
using namespace player;
class nplTread :public  QThread//, public QObject
{
    Q_OBJECT
public:
    nplTread();
    ~nplTread();
// 	  void import(const QMimeData *data,int row);
// 	  void init(const QList <QUrl> urls,int i);
    void setStringL(QStringList l);
    void setUrls(QList <QUrl> l);
    void setPos(int num);
protected:
    void run();

private:
    QList <QUrl> urlList;
    QStringList  sList;
    int pos;

    inline bool isDirectory(const QString &url);
    inline bool isAudio(const QString &url);

    bool isM3u(const QString s);

    void addDirectory(const QString &url);
    bool addMedia(const QString &url);

    QWidget *w;
    bool canceled;
signals:
    void insert(int, nplTrack*);
    void added(int);

};

#endif
