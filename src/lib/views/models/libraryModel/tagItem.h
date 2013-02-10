#ifndef TAG_ITEM_H 
#define TAG_ITEM_H

#include <tagInfo.h>
#include<queries/abstractQuery.h>
#include<QVector>
#include <KIcon>
#include <databaseEvent.h>

#include<QDebug>
namespace views
{
// class tagItem;
// typedef QSharedPointer<views::tagItem> tagItemP;

class tagItem :public QObject
{
	Q_OBJECT
	public:
		tagItem(audioFiles::tagInfo tag,QObject *parent=0);
		tagItem(const views::tagItem &other);
		tagItem(QObject *parent=0);
		
		void operator= (const views::tagItem &other);
		  
		tagItem* parentItem() const
		{
			return dynamic_cast<tagItem*>( parent() );
		}
		
		QVariant data()
		{
			return _tag.data();
		}
		
		QVector<views::tagItem*>* tags(int type)
		{
			return &(_tags[type].vec);
		}
		
		tagItem* itemAt(int type,int row);
		
		int size(int type);
		
		
 		bool hasDataPopulated(int type);
		
		bool populate(int type,bool force=false);		

		database::abstractQuery* filter();
		void setCustomFilter(database::abstractQuery *q);
		
		/*   some function for convinience  */
		
		
		//returns an appropriate qvariant for Decoration role
		virtual QVariant icon();
		
		virtual int type()
		{
			return _tag.type();
		}
		
		
		virtual void appendItem(audioFiles::tagInfo &tag,int type);
		
	private:
		audioFiles::tagInfo _tag;
		database::abstractQuery *_customFilter;
		
		class tagVec
		{
			public:
				tagVec():isSelected(false),isDirty(true){};
				bool isSelected;
				bool isDirty;
				QVector<tagItem*> vec;
		};
		
		QVector<struct tagVec> _tags;
		
		void setNeedUpdate(int t);
		
		bool doPopulate(int type);        
		
	private slots:
		void dbEvents(database::dbEventP e);
		
	signals:
		void needUpdate(int);
};



};

#endif
