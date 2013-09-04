#include"tagItemHead.h" 
#include <viewsFunc.h>
#include<database/database.h>
#include<views/models/urlRole.h>
views::tagItemHead::tagItemHead(QObject *parent)   :tagItem() ,_customFilter(0)
{   
    setParent(parent);
    connect(database::db(),SIGNAL( newEvent(database::dbEventP)),this,SLOT(checkUpdate(database::dbEventP)) );    
}

views::tagItemHead::~tagItemHead()
{
    clear();
    if(_customFilter!=0)
        delete _customFilter;
}


QVariant views::tagItemHead::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation!=Qt::Horizontal)
        return QVariant();
    
    if(role == Qt::DisplayRole )
    {
        QString s=views::tagName(section);
        return QVariant(s);
    }
    
    if(role == TAG_ROLE)
    {
        if(section>0 && section<Basic::FRAME_NUM)
            return QVariant(section);
        
        return QVariant(Basic::INVALID);
    }
    
    
    return standardItem::headerData(section, orientation, role);
}

int views::tagItemHead::nextData() const
{
    if(_tagsL.isEmpty())
    {
        return Basic::INVALID;
    }
    return _tagsL[0];
            
}



void views::tagItemHead::checkUpdate(database::dbEventP e)
{
    //TODO fix this bulsheet and write a more efficienty update mechanism
    
    qDebug()<<"DB UP "<<e->type();
    using namespace audioFiles;
    using namespace database;
    
//     int type=nextData();
    
    if(rowCount()==0)
    {
        return ;
    }
    
    if(_isDirty )
    {
        return ;
    }

    int t=e->type();
    if(t==FILES_REM || t==FILES_INS || t==UPDATE_COMP || t==RESCAN_COMP || t==NEW_CONN)
    {        
        setNeedUpdate();
    }
    
    qDebug()<<"DB UP ";
    QList<int>l;
    l<<Basic::ALBUM<<Basic::ALBUM_ARTIST<<Basic::ARTIST<<Basic::LEAD_ARTIST;
    
    if(e->type()==FILES_CHANG)
    {        
        dbEventAF *ev = static_cast<dbEventAF*>( e.data() );

        foreach(const audioFile &f, ev->files)
        {
            if(_customFilter!=0 && _customFilter->match(f) )
            {
                setNeedUpdate();
                return ;
            }
            
            QList<tagChanges> cl=f.tagChanged();
            foreach(tagChanges c,cl)
            {
                qDebug()<<"C "<<c.tag;
                if(_tagsL.contains(c.tag))
                {
                    qDebug()<<"need";
                    setNeedUpdate();
                    return ;
                }
            }

            foreach(int i,_tagsL)
            {
                if(l.contains(i) )
                {
                    foreach(tagChanges c,cl)
                    {
                        if(l.contains(c.tag))
                        {
                            qDebug()<<"need2";
                            setNeedUpdate();
                            return ;
                        }
                    }
                    return ;
                }
            }
        }
    }
}

void views::tagItemHead::setNeedUpdate()
{
    _isDirty=true;
    emit updateNeeded(); 
}

void views::tagItemHead::updateIfDirty()
{
    if(_tagsL.isEmpty())
    {
        return ;
    }
    if(_isDirty)
    {
        update();
    }
}
