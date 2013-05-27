#include"audioFilesSelf.h"
#include"audioFile.h"
#include <QEvent>
#include<QCoreApplication>

#define CH_EVENT QEvent::User

void audioFiles::init()
{
    qRegisterMetaType<audioFiles::tagChangesL>("audioFiles::tagChangesL");
    qRegisterMetaType<audioFiles::audioFile>("audioFiles::audioFile");    
    audioFiles::audioFilesSelf::_self=new audioFilesSelf;
}

void audioFiles::cleanUp()
{
    delete audioFilesSelf::_self;
}

audioFiles::audioFilesSelf* audioFiles::self()
{
    return audioFilesSelf::_self;
}

audioFiles::audioFilesSelf* audioFiles::audioFilesSelf::_self=0;

void audioFiles::audioFilesSelf::emitChanged(audioFiles::audioFile f)
{
    chEvent *e=new chEvent(f);
    QCoreApplication::postEvent(this,e);
}

void audioFiles::audioFilesSelf::customEvent(QEvent* event)
{
    if(event->type()==CH_EVENT)
    {
        chEvent *e=static_cast<chEvent*>(event);
        emit changed(e->file);
    }
    QObject::customEvent(event);
}


audioFiles::audioFilesSelf::chEvent::chEvent(audioFiles::audioFile f)
:QEvent(CH_EVENT)
{
    file=f;
}
