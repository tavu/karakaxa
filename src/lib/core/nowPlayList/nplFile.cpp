#include"nplFile.h"
#include<QDebug>
// #include<player.h>
#include"../core.h"
#include"../../files/fileTags.h"
using namespace audioFiles;
core::nplFile::nplFile(QString s)
        :nplTrack()
{
    file=new audioFile(s);

    if (file==0 )
    {
        qDebug()<<"null file";
        ok=false;
    }
    else if(!core::exists(s) )
    {
	   qDebug()<<"file does not exist";
	   ok=false;
    }
    else
    {
 	   connect(file,SIGNAL(changed(audioFiles::tagChangesL)),this,SLOT(emitCh() ) );
    }

    _loadFlag=audioFile::ONDATAB|audioFile::ONCACHE|audioFile::TITLEFP;

}

void core::nplFile::emitCh()
{
    nplTrack::emitChanged();
}

core::nplTrack* core::nplFile::clone()
{
    return new nplFile( file->path() );
}

void core::nplFile::play()
{
    int c=file->tag(COUNTER).toInt();
    file->setTag(COUNTER,QVariant(c+1) );
}

QVariant core::nplFile::artist()
{
    if(file==0)	return QVariant();

    return file->albumArtist();
}


core::nplFile::~nplFile()
{
   delete file;
}

int core::nplFile::length()
{
    if(file==0)	return 0;
    return file->tag(LENGTH).toInt();
}

QString core::nplFile::path()
{
    if(file==0)	return QString();
    return file->path();
}

QString core::nplFile::title()
{
    if(file==0)	return QString();
    return file->tag(TITLE,_loadFlag).toString();
}

int core::nplFile::type()
{
    return NPLAUDIOFILE;
}

QString core::nplFile::cover()
{
    if(file==0)	return QString();
    return file->cover();
}

QVariant core::nplFile::tag(int t)
{
    if(file==0)	return QVariant();
    return file->tag(t,_loadFlag);
}

audioFile* core::nplFile::getAudioFile()
{
    return file;
}