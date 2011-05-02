#ifndef TAGS_H
#define TAGS_H

#include "tagsTable.h"
#include"audioFiles.h"

#include <fileref.h>
#include <mpegfile.h>
#include <tag.h>


//---QT---
#include<QObject>
#include <QStringList>
#include <tstringlist.h>

namespace audioFiles
{

class fileTags
{
    //      using namespace TagLib;
    public:
	fileTags(QString);
	~fileTags();


    private:
	QString 			path;


    protected:
	mutable int 			err;
	TagLib::FileRef			file;
	TagLib::Tag 			*tags;
	TagLib::AudioProperties 	*properties;


	static TagLib::String  toTString(QString s) ;
	static QString toQString(TagLib::String s) ;
	static void toStringList( TagLib::StringList sl,QStringList &ql);


    public:
	virtual QVariant		tag(tagsEnum t)	const;
	virtual bool 			setTag(tagsEnum,const QVariant &var);

	virtual QVariant 		title () const ;
	virtual QVariant 		artist () const ;
	virtual QVariant 		album () const ;
	virtual QVariant 		comment () const;
	virtual QVariant 		genre () const ;
	virtual QVariant 		year () const ;
	virtual QVariant 		track () const;


	virtual QVariant 		bitrate () const ;
	virtual QVariant		length()   const;


	virtual bool 			setTitle (const QString &s);
	virtual bool 			setArtist(const QString &s);
	virtual bool 			setAlbum (const QString &s);
	virtual bool 			setComment (const QString &s);
	virtual bool 			setGenre (const QString &s);
	virtual bool 			setYear (const unsigned int &year);
	virtual bool 			setTrack (const unsigned int &i);

	virtual void 			save();
	virtual void			getTags(audioFiles::tagRecord*);

	inline bool isNull()  const
	{
	    return file.isNull();
	}

	inline bool isValid() const
	{
	    if (file.isNull() )
	    {
		return false;
	    }

	    return file.file()->isValid();
	}

	inline QString getPath() const
	{
	    return path;
	}


	inline int error() const
	{
	    return err;
	}


// 	static const int NULLFILE;
// 	static const int INVALIDF;
// 	static const int WRONGFT;
// 	static const int NSTAG;
// 	static const int OK;
};//class
};//player
#endif
