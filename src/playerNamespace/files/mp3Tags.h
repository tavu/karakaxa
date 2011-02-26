#ifndef MP3TAGS_H
#define MP3TAGS_H


#include <textidentificationframe.h>
#include <fileref.h>

#include "tagsTable.h"

#include <textidentificationframe.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v2frame.h>
#include <popularimeterframe.h>
#include <tag.h>

#include"fileTags.h"

//---QT---
#include<QObject>
#include <QStringList>
#include<QString>

#include <tstringlist.h>

namespace audioFiles
{

class mp3Tags :public fileTags
{
    //      using namespace TagLib;
public:
    mp3Tags(QString);

private:


    TagLib::ID3v2::Tag 	*id3v2tag;


public:
// 	       virtual /*tagsTable*/		getTagsTable();

    virtual QVariant		composer() const;
    virtual QVariant 		counter( ) const;
    virtual QVariant		rating() const;
    virtual QVariant 		leadArtist () const ;


    virtual bool 		setLeadArtist (const QString &s);
    virtual bool		setComposer(const QString &s);
    virtual bool 		setRating(int rating);
    virtual bool 		setCounter(const unsigned int &num);

    virtual bool 		setArtists (const QStringList &l);
    virtual QStringList 	artists () const ;

    virtual QVariant		tag(player::tagsEnum t) const;
    virtual bool		setTag(player::tagsEnum t,const QVariant &var);
    virtual int			originalRating() const;
    virtual bool		setOriginalRating(const unsigned int &num);
};//class
};//player
#endif
