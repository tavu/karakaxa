#include"playlist.h"
#include <qthread.h>
#include"../func.h"
#include<QThread>
#include<QCoreApplication>

void core::playlist::insert(int pos, core::nplPointer p)
{
    nplList l;
    l.append(p);
    insert(pos,l);
}

void core::playlist::insert(int pos, nplList l)
{
    QEvent *e=new insertEv(pos,l);
    if(QThread::currentThread()==core::mainThr() )
    {
        QCoreApplication::sendEvent(this,e);
    }
    else
    {
        QCoreApplication::postEvent(this,e);
    }
}

void core::playlist::remove(int pos)
{
    remove(pos,1);
}

void core::playlist::remove(int pos,int num)
{
    QEvent *e=new removeEv(pos,num);

    if(QThread::currentThread()==core::mainThr() )
    {
        QCoreApplication::sendEvent(this,e);
    }
    else
    {
        QCoreApplication::postEvent(this,e);
    }
}

void core::playlist::move(int pos,int dest)
{    
    move(pos,1,dest);
}

void core::playlist::move(int pos, int num,int dest)
{
    QEvent *e=new moveEv(pos,num,dest);
    if(QThread::currentThread()==core::mainThr() )
    {
        QCoreApplication::sendEvent(this,e);
    }
    else
    {
        QCoreApplication::postEvent(this,e);
    }

}

void core::playlist::clear()
{
    QEvent *e=new clearEv();
    if(QThread::currentThread()==core::mainThr() )
    {
        QCoreApplication::sendEvent(this,e);
    }
    else
    {
        QCoreApplication::postEvent(this,e);
    }

}

void core::playlist::clearEvent(core::playlist::clearEv* event)
{
    emit aboutToClear();
    trackList.clear();
    emit cleared();
    event->accept();
}

void core::playlist::insertEvent(core::playlist::insertEv* event)
{
    int pos=event->pos();
    nplList l=event->list();

    if(pos<0 || pos>trackList.size() )
    {
        pos=trackList.size();
    }

    if(l.isEmpty() )
    {
        event->ignore();
        return ;
    }
    
    emit aboutToInsertTracks(pos,l.size() );
    for(int i=0;i<l.size();i++)
    {
       trackList.insert (pos+i,l[i] );
    } 
    emit tracksInserted(pos,l.size() );

    event->accept();
}

void core::playlist::moveEvent(core::playlist::moveEv* event)
{
    int pos =event->pos();    
    int num=event->num();
    int dest=event->dest();
    if(pos<0 || pos>trackList.size() || num<1 )
    {
        event->ignore();
        return ;
    }

    if(pos+num>trackList.size() )
    {
        num=trackList.size()-pos;
    }

    if(dest<0|| dest>=trackList.size() )
    {
        dest=trackList.size()-1;
    }

    emit aboutToMoveTrack(pos,num,dest);
    for(int i=0;i<num;i++)
    {
       trackList.move(pos,dest);       
    }
    emit trackMoved(pos,num,dest);
    event->accept();
}

void core::playlist::removeEvent(core::playlist::removeEv* event)
{
    int pos=event->pos();
    int num=event->num();

    if(pos<0 || pos>trackList.size() || num<1 )
    {
        event->ignore();
        return ;
    }

    if(pos+num>trackList.size() )
    {
        num=trackList.size()-pos;
    }

    emit aboutToRemoveTracks(pos,num);
    for(int i=0;i!=num;i++)
    {
        trackList.removeAt(pos);
    }
    emit trackRemoved(pos,num);

    event->accept();

}

void core::playlist::customEvent(QEvent* event)
{
    switch(event->type() )
    {
        case INSERT_EVENT:
        {
            insertEvent(static_cast<insertEv*>(event) );
            break ;
        }
        case REMOVE_EVENT:
        {
            removeEvent(static_cast<removeEv*>(event) );
            break ;
        }
        case MOVE_EVENT:
        {
            moveEvent(static_cast<moveEv*>(event) );
            break ;
        }
        case CLEAR_EVENT:
        {
            clearEvent(static_cast<clearEv*>(event) );
            break  ;
        }
        default :
        {
            break ;
        }
    }
    
    QObject::customEvent(event);
}
