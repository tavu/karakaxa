#ifndef TAG_SELECTOR_H
#define TAG_SELECTOR_H

#include <tagInfo.h>
#include<queries/abstractQuery.h>
#include<QVector>
#include <KIcon>
#include <databaseEvent.h>
#include <core/standardModel/standardModel.h>

namespace views
{

class tagSelector :public QObject
{
    Q_OBJECT
    public:
        tagSelector(audioFiles::tagInfo tag,QObject *parent=0);
        tagSelector(QObject *parent=0);

        virtual ~tagSelector();
        
        void operator= (const views::tagSelector &other);

        tagSelector* parentItem() const
        {
            return dynamic_cast<tagSelector*>( parent() );
        }

        QVariant data()
        {
            return _tag.data();
        }
        
        const audioFiles::tagInfo& tag()
        {
            return _tag;
        }

        QVector<views::tagSelector*>* tags(int type) 
        {
            if(!_tags.contains(type))
            {
                return 0;
            }
            tagVec *v=_tags[type];
            return v->vec;
        }

        tagSelector* itemAt(int type,int row);

        int size(int type);


        bool hasDataPopulated(int type) const;

        bool populate(int type,bool force=false);

        database::abstractQuery* filter() const;
        void setCustomFilter(database::abstractQuery *q);


        database::abstractQuery *customFilter()
        {
            return _customFilter;
        }
        
        bool isDirty(int t) const;
        void setDirty(int t);
        
        //returns an appropriate qvariant for Decoration role
        virtual QVariant icon();

        virtual int type() const
        {
            return _tag.type();
        }

        virtual QVariant data(int t);

        virtual void appendItem(audioFiles::tagInfo tag,QVector<tagSelector*> *tagL);
        
        
        //standardItem
        virtual int columnCount() const;
        virtual QVariant data (int column, int role = Qt::UserRole + 1 ) const;
        
    private:
        audioFiles::tagInfo _tag;
        database::abstractQuery *_customFilter;

        class tagVec
        {
            public:
                tagVec():isSelected(false),isDirty(true) 
                {
                    vec=new QVector<tagSelector*>();
                }
                ~tagVec()
                {
                    for(int i=0;i<vec->size();i++)
                    {
                        delete vec->value(i);
                    }
                    delete vec;
                }
                
                bool isSelected;
                bool isDirty;
                QVector<tagSelector*> *vec;
        };

        QMap<int,struct tagVec*> _tags;

        void setNeedUpdate(int t);

        bool doPopulate(int type);
        
        inline void clear(int t);        
};



};

#endif
