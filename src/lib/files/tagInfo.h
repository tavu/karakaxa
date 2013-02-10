#ifndef TAGINFO_H
#define TAGINFO_H

#include<QObject>
#include"tagsTable.h"

namespace audioFiles
{
/*
 * This is a very simple class from tag information.
 * The attributes of the tag can be added to QObject properties such as the id of the album etc
 */

class tagInfo :public QObject
{
	Q_OBJECT
	public:
		tagInfo()
		{
			_type=INVALID;
		}
		
		tagInfo(int type,QVariant data,QObject *parent=0) :QObject(parent)
		{
			_type=type;
			_data=data;
		}
		
		tagInfo(const tagInfo &other) :QObject( other.parent() )
		{
			_data=other._data;
			_type=other._type;
 			foreach(const QByteArray &prop, other.dynamicPropertyNames() )
 			{
 				setProperty( prop.constData(), other.property( prop.constData() ) ); 
 			}
		}
		
		int type()
		{
			return _type;
		}
		
		void operator= (tagInfo other)
		{
			_data=other._data;
			_type=other._type;
			 
			foreach(const QByteArray &prop, other.dynamicPropertyNames() )
 			{
 				setProperty( prop.constData(), other.property( prop.constData() ) ); 
 			}
		}
		
		QVariant data()
		{
			return _data;
		}
		
		void setData(QVariant d)
		{
			_data=d;
		}
		
	protected:
		QVariant _data;
		int _type;
};
// Q_DECLARE_METATYPE(tagInfo);
}
// Q_DECLARE_METATYPE(audioFiles::tagInfo);
#endif
