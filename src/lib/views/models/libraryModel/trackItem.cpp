#include"trackItem.h"
#include<views/models/urlRole.h>
#include<KUrl>
#include<QDebug>

using namespace audioFiles;

views::trackItem::trackItem(audioFiles::audioFile f,QObject *parent)
  :standardItem(),
  file(f)
{
    connect(&file,SIGNAL(changed(audioFiles::tagChangesL)),this,SLOT(changed(audioFiles::tagChangesL)) );
}

views::trackItem::trackItem(tagInfo t, QObject* parent) :standardItem()
{
    file=audioFiles::audioFile(t.property(Basic::PATH).toString() );
    connect(&file,SIGNAL(changed(audioFiles::tagChangesL)),this,SLOT(changed(audioFiles::tagChangesL)) );
}


void views::trackItem::changed(audioFiles::tagChangesL c)
{
    if(c.size()==1)
    {
        standardItem::dataChanged(c.at(0).tag );
    }
    else
    {
        standardItem::dataChanged(0,Basic::FRAME_NUM-1);
    }
}


QVariant views::trackItem::data(int column, int role) const
{    
    if(role==Qt::DisplayRole || role==Qt::ToolTipRole || role==Qt::EditRole)
    {
        return views::pretyTag(file.tag(column),column );
    }
    
    if(role==URL_ROLE)
    {
        KUrl u( file.path() );
        return QVariant(u);
    }
    
    if(role == TAG_ROLE )
    {
        return QVariant(column);
    }
    
    if(role==DISABLE_ROLE)
    {
        return QVariant(!file.isValid());
    }


    return QVariant();
}

bool views::trackItem::setData(const QVariant& value, int column, int role)
{
    if(role==Qt::DisplayRole ||role==Qt::EditRole )
    {
        file.setTag(column,value);
        if(file.error()==Basic::OK)
        {
    // 	    dataChanged(column,column);
            return true;
        }
    }

    return false;
}

bool views::trackItem::canFetchMore() const
{
    return false;
}

