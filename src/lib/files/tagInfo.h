#ifndef TAGINFO_H
#define TAGINFO_H

#include<QObject>
#include<Basic/tagsTable.h>
#include<QVariant>
#include<QMap>
namespace audioFiles
{
/*
 * This is a very simple class from tag information.
 * The attributes of the tag can be added to QObject properties such as the id of the album etc
 */


class tagInfo
{
	public:
		tagInfo()
		{
			_type=Basic::INVALID;
		}
		
		tagInfo(const tagInfo &t ) :_type(t._type),_data(t._data),_map(t._map)
                {                        
                }
		
		tagInfo(int type,QVariant data,QObject *parent=0)
		{
			_type=type;
			_data=data;
		}
		
		tagInfo* operator=(const tagInfo &t)
                {
                    _type=t._type;
                    _data=t._data;
                    _map=QMap<int,QVariant>(t._map);
                    return this;
                }
		
		int type() const
		{
			return _type;
		}

		QVariant data() const
		{
			return _data;
		}
		
		void setData(QVariant d)
		{
			_data=d;
		}
		
		QVariant property(int t) const
                {
                    return _map.value(t);
                }
                
                void setProperty(int t,QVariant v)
                {
                    _map.insert(t,v);
                }
                
                const QMap<int,QVariant>& map()
                {
                    return _map;
                }
		
	protected:
		QVariant _data;
		int _type;
                QMap<int,QVariant> _map;
};
// Q_DECLARE_METATYPE(tagInfo);
}
// Q_DECLARE_METATYPE(audioFiles::tagInfo);
#endif
