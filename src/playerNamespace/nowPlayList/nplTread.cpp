#include"nplTread.h"
#include<KMimeType>
#include<QDirIterator>
#include<QDebug>
#include"nplFile.h"
#include<player.h>
#include <QHBoxLayout>
#include <QProgressBar>
#include"nplStream.h"
nplTread::nplTread()
        :QThread(),
        canceled(false)
{
    w=new QWidget();
    QHBoxLayout *l=new QHBoxLayout(w);

    QLabel *sl=new QLabel(tr("Loading"),w);
    l->addWidget(sl);

    statusBar.addPermanentWidget(w);

    connect(this,SIGNAL(finished() ),this ,SLOT(deleteLater () ),Qt::QueuedConnection );

}


nplTread::~nplTread()
{
    statusBar.removeWidget(w);
    qDebug()<<"quit";
    delete w;
}

void nplTread::run()
{
    foreach(QUrl url, urlList)
    {
        if (canceled)
        {
            return ;
        }
        addMedia(url.toLocalFile() );
    }

    foreach(QString url, sList)
    {
        if (canceled)
        {
            return ;
        }
        addMedia(url );
    }
}

bool nplTread::addMedia(const QString &url)
{
    qDebug()<<"url"<<url;
    if (player::isDirectory(url) )
    {
        addDirectory(url);
        return true;
    }

    if (player::isStream(url) )
    {
        qDebug()<<"stream"<<url;
        nplTrack *t=new nplStream(url);
        npList.insert(pos,t);
        pos++;
    }

    if (player::isPlaylist(url) )
    {
        player::m3uPl m3u(url);
        m3u.load();

        for (int i=0;i<m3u.size();i++)
        {
            addMedia(m3u.item(i));
            pos++;
        }
        return true;
    }

    npList.addAudio(url,pos);
    pos++;
    return true;
}


void nplTread::setUrls(QList <QUrl> l)
{
    urlList=l;
}

void nplTread::setStringL(QStringList l)
{
    sList=l;
}

void nplTread::setPos(int num)
{
    pos=num;
}

void nplTread::addDirectory(const QString &url)
{
    QDirIterator it(url,QDir::Files|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    QFileInfo info;
    while (it.hasNext() )
    {
        it.next();
        info=it.fileInfo();
        npList.addAudio(info.filePath(),pos );
        pos++;
    }
}
