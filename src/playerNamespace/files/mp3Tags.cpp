#include"mp3Tags.h"
#include<QDebug>
#include<player.h>
audioFiles::mp3Tags::mp3Tags(QString url)
         :fileTags(url),
        id3v2tag(0)
{
    using namespace TagLib;
//     file =new MPEG::File(path);

//     TagLib::FileRef file(url.toLocal8Bit().constData());
    
    if (file.isNull() )
    {
        err=NULL_FILE;
        return;
    }

    MPEG::File *f=dynamic_cast<MPEG::File *>(file.file() );

    if (f!=0)
    {
        id3v2tag = f->ID3v2Tag(true);
    }
    else
    {
        err=WRONG_FILETYPE;
    }
}

QStringList audioFiles::mp3Tags::artists() const
{
    using namespace TagLib;
    QStringList l;

    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return l;

    }


    ID3v2::FrameList fList=id3v2tag->frameList("TPE1");

    if (fList.isEmpty() )	return l;

    ID3v2::FrameList::Iterator it = fList.begin();

    ID3v2::TextIdentificationFrame *frame=static_cast<ID3v2::TextIdentificationFrame*> (*it);

// 	  toQStringList( frame->fieldList() , l);

    StringList tl=frame->fieldList();
    this->toStringList(tl,l);
    err=0;

    return l;
}


QVariant audioFiles::mp3Tags::counter() const
{
    using namespace TagLib;
    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return QVariant();
    }

    ID3v2::FrameList fList=id3v2tag->frameList("POPM");

    if (fList.isEmpty() )	return 0;

    ID3v2::FrameList::Iterator it = fList.begin();

    ID3v2::PopularimeterFrame *frame=static_cast<ID3v2::PopularimeterFrame*> (*it);

    err=OK;

    return frame->counter();
}

QVariant audioFiles::mp3Tags::rating() const
{
    int r=originalRating();
            
    int n=r/25;
    if (r%25>0 && n!=10) 
    {
	n++;
    }
    return QVariant(n);
}

int audioFiles::mp3Tags::originalRating() const
{
  //this function gets the rating number from the mp3 file.
  //that number is betwoin 0-255. 0 is the unrating
    using namespace TagLib;
    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return 0;
    }

    ID3v2::FrameList fList=id3v2tag->frameList("POPM");

    if (fList.isEmpty() )	return 0;

    ID3v2::FrameList::Iterator it = fList.begin();

    ID3v2::PopularimeterFrame *frame=static_cast<ID3v2::PopularimeterFrame*> (*it);

    err=0;

    return frame->rating();        
}


QVariant audioFiles::mp3Tags::leadArtist() const
{
    using namespace TagLib;

    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return QVariant();
    }
    ID3v2::FrameList fList=id3v2tag->frameList("TPE2");

    if (fList.isEmpty() )	return QString();

    ID3v2::FrameList::Iterator it = fList.begin();

    err=0;

    return toQString( (*it)->toString() );
}

QVariant audioFiles::mp3Tags::composer() const
{
    using namespace TagLib;

    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return QVariant();
    }

    ID3v2::FrameList fList=id3v2tag->frameList("TCOM");

    if (fList.isEmpty() )	return QString();

    ID3v2::FrameList::Iterator it = fList.begin();

    err=0;

    return toQString( (*it)->toString() );
}


bool audioFiles::mp3Tags::setArtists(const QStringList &l)
{
    using namespace TagLib;
    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return true;

    }
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }
    err=0;

    ID3v2::TextIdentificationFrame *frame;

    ID3v2::FrameList fList=id3v2tag->frameList("TPE1");

    if (fList.isEmpty () )
    {
        frame= new ID3v2::TextIdentificationFrame ("TPE1",String::UTF8 );
        id3v2tag->addFrame(frame);
    }
    else
    {
        ID3v2::FrameList::Iterator it = fList.begin();
        frame=static_cast<ID3v2::TextIdentificationFrame *> (*it);
        frame->setTextEncoding(String::UTF8);
    }

    StringList sList;

    for (int i=0;i<l.size();i++)
    {
        sList.append( toTString( l.at(i) ) );
    }

    frame->setText(sList );

    

    return true;
}


bool audioFiles::mp3Tags::setLeadArtist (const QString &s)
{
    using namespace TagLib;

    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return false;

    }
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    ID3v2::TextIdentificationFrame *frame;

    ID3v2::FrameList fList=id3v2tag->frameList("TPE2");

    if (fList.isEmpty () )
    {
        frame= new ID3v2::TextIdentificationFrame ("TPE2",String::UTF8 );
        id3v2tag->addFrame(frame);
    }
    else
    {
        ID3v2::FrameList::Iterator it = fList.begin();
        frame=static_cast<ID3v2::TextIdentificationFrame *> (*it);
        frame->setTextEncoding(String::UTF8);
    }

    frame->setText(toTString(s) );
    
    err=0;

    return true;
}

bool audioFiles::mp3Tags::setComposer (const QString &s)
{
    using namespace TagLib;

    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return false;

    }
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }
    ID3v2::TextIdentificationFrame *frame;

    ID3v2::FrameList fList=id3v2tag->frameList("TCOM");

    if (fList.isEmpty () )
    {
        frame= new ID3v2::TextIdentificationFrame ("TCOM",String::UTF8 );
        id3v2tag->addFrame(frame);
    }
    else
    {
        ID3v2::FrameList::Iterator it = fList.begin();
        frame=static_cast<ID3v2::TextIdentificationFrame *> (*it);
        frame->setTextEncoding(String::UTF8);
    }

    frame->setText(toTString(s) );
    
    err=0;

    return true;
}

bool audioFiles::mp3Tags::setRating( int num)
{
    num*=25;
    return setOriginalRating(num);
}

bool audioFiles::mp3Tags::setOriginalRating(const unsigned int &num)
{
    using namespace TagLib;

    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return false;

    }
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    ID3v2::PopularimeterFrame *frame;

    ID3v2::FrameList fList=id3v2tag->frameList("POPM");

    if (fList.isEmpty () )
    {
        frame=new ID3v2::PopularimeterFrame();
        frame->setCounter(0);
        id3v2tag->addFrame(frame);
    }
    else
    {
        ID3v2::FrameList::Iterator it = fList.begin();
        frame=static_cast<ID3v2::PopularimeterFrame*> (*it);
    }

    frame->setRating(num);

    

    return true;
}

bool audioFiles::mp3Tags::setCounter(const unsigned int &num)
{
    using namespace TagLib;

    if (!id3v2tag)
    {
        if (isNull() )
        {
            err=NULL_FILE;
        }
        else
        {
            err=WRONG_FILETYPE;
        }
        return false;

    }
    if (!isValid() )
    {
        err=INVALID_FILE;
        return false;
    }

    ID3v2::PopularimeterFrame *frame;

    ID3v2::FrameList fList=id3v2tag->frameList("POPM");

    if (fList.isEmpty () )
    {
        frame=new ID3v2::PopularimeterFrame();
        frame->setRating(0);
        id3v2tag->addFrame(frame);
    }
    else
    {
        ID3v2::FrameList::Iterator it = fList.begin();
        frame=static_cast<ID3v2::PopularimeterFrame*> (*it);
    }

    frame->setCounter(num);

    
    err=0;
    return true;
}

QVariant audioFiles::mp3Tags::tag(player::tagsEnum t) const
{

    switch (t)
    {
    case TITLE:
    {
        return title();
    }
    case ALBUM:
    {
// 	       qDebug()<<album();
        return album();
    }
    case ARTIST:
    {
        return artist();
    }
    case LEAD_ARTIST:
    {
        return leadArtist();
    }
    case COMPOSER:
    {
        return composer();
    }
    case GENRE:
    {
        return genre();
    }
    case COMMENT:
    {
        return comment();
    }
    case TRACK:
    {
        return track();
    }
    case YEAR:
    {
        return year();
    }
    case LENGTH:
    {
        return length();
    }
    case RATING:
    {
        return rating();
    }
    case BITRATE:
    {
        return bitrate();
    }
    default:
    {
        err=NS_TAG;
        return QVariant();

    }
    }
}

bool audioFiles::mp3Tags::setTag(player::tagsEnum t,const QVariant &var)
{

    switch (t)
    {
    case TITLE:
    {
        return setTitle(var.toString() );
    }
    case ALBUM:
    {
        return setAlbum(var.toString());
    }
    case ARTIST:
    {
        return setArtist(var.toString());
    }
    case LEAD_ARTIST:
    {
        return setLeadArtist(var.toString());
    }
    case COMPOSER:
    {
        return setComposer(var.toString());
    }
    case GENRE:
    {
        return setGenre(var.toString());
    }
    case COMMENT:
    {
        return setComment(var.toString());
    }
    case TRACK:
    {
        return setTrack(var.toInt());
    }
    case YEAR:
    {
        return setYear(var.toInt() );
    }
    case RATING:
    {
        return setRating(var.toInt());
    }
    default:
    {
        err=NS_TAG;
        return false;

    }
    }
}
