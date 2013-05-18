#include"tagItemModel.h"
#include<Basic/tagsTable.h>
#include<QDebug>
#include<KUrl>

#include"../urlRole.h"
#include"../../viewsFunc.h"
#include"../../decoration/decoration.h"

views::tagItemModel::tagItemModel(QObject *parent) :QAbstractItemModel(parent)
{
	_tags<<Basic::ALBUM_ARTIST<<Basic::ALBUM<<Basic::FILES;
	head=new tagItem();
	head->populate(_tags[0]);
        connect(head,SIGNAL(needUpdate(int)),this,SLOT(updateData(int)));
	setProperty(SPAN_PROP,QVariant(true) );
}

views::tagItemModel::~tagItemModel()
{
	delete head;
}

int views::tagItemModel::rowCount ( const QModelIndex & parent ) const
{
	tagItem* item=itemFromIndex(parent);

	int type=nextItemType(item);
	return item->size(type);
}

int views::tagItemModel::columnCount ( const QModelIndex & parent  ) const
{
	if(!parent.isValid() )
	{
		return  Basic::FRAME_NUM;
	}
	
	tagItem* item=itemFromIndex(parent);
 	int type=nextItemType(item);
	if(type==Basic::FILES)
	{
		return Basic::FRAME_NUM;
	}
	
// 	return audioFiles::FRAME_NUM;
	return 1;
}

QVariant views::tagItemModel::data ( const QModelIndex & index, int role ) const
{
	tagItem* item=itemFromIndex(index);
// 	if(item==head)
// 	{
// 
// 		return QVariant();
// 	}
		
	if(item->type()==Basic::FILES)
	{
		audioFiles::audioFile f=qvariant_cast <audioFiles::audioFile>(item->data() );
		return fileData(f,index.column(),role);
	}
	
	if(role==Qt::DisplayRole)
	{
		QVariant var=item->data().toString();
		QString s=var.toString().trimmed();		
		if(s.isNull()||s.isEmpty())
		{
			return QVariant(tr("Unknown") );
		}
		return var;
	}
	if(role==OPACITY_ROLE)
	{
		QString s=item->data().toString().trimmed();
		if(s.isNull()||s.isEmpty())
		{
			return QVariant(true);
		}
		return QVariant(false);
	}
	if( role==Qt::DecorationRole)
	{
		return QVariant(item->icon() );
	}
	if(role==TAG_ROLE)
	{
		return item->type();
	}
	if(role==Qt::SizeHintRole)
	{
		return QVariant(QSize(20,50) );
	}
	if(role==SPAND_ROLE)
	{
		if(nextItemType(item)==Basic::FILES )
		{
			return QVariant(false);
		}
		else
		{
			return QVariant(true);
		}
	}
	return QVariant();
}
QVariant views::tagItemModel::fileData(audioFiles::audioFile& f, int column, int role) const
{
    if(!f.isValid())
    {
        return QVariant();
    }

    if(role==Qt::DisplayRole || role==Qt::ToolTipRole || role==Qt::EditRole)
    {
	   return views::pretyTag(f.tag(column),column );
    }
    if(role==URL_ROLE)
    {
        KUrl u( f.path() );
        return QVariant(u);
    }
    if(role == TAG_ROLE )
    {
        return QVariant(column);
    }
	
	return QVariant();
}

QVariant views::tagItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)
    {
        if (section==Basic::TRACK)
        {
            return QVariant(QString("#") );
        }
        return QVariant(tagName(section) );
    }

    if(role==Qt::EditRole)
    {
        return QVariant(tagName(section) );
    }

    if(role==Qt::DecorationRole)
    {
        return QVariant(decor->tagIcon( section) );
    }

    return QAbstractItemModel::headerData(section,orientation,role);
}

QModelIndex views::tagItemModel::index ( int row, int column, const QModelIndex &parent  ) const
{
	tagItem* item=itemFromIndex(parent);
	
	int type=nextItemType(item);
	if(type<0)
	{
		return QModelIndex();
	}
	
	item=item->itemAt(type,row);
	
	if(item==0 )
	{
		return QModelIndex();
	}
	
	if(type==Basic::FILES)
	{
		if(column>=Basic::FRAME_NUM)
		{
			return QModelIndex();
		}
	}
	else if(column!=0)
	{
		return QModelIndex();
	}
	
	return createIndex(row,column,item );
}

QModelIndex views::tagItemModel::parent ( const QModelIndex & index ) const
{
	tagItem* item=itemFromIndex(index);
	if(item==head)
	{
		return QModelIndex();
	}
	item=item->parentItem();
	if(item==head)
	{
		return QModelIndex();
	}

	return createIndex(0,0,item );
}

bool views::tagItemModel::canFetchMore(const QModelIndex& parent) const
{
	tagItem* item=itemFromIndex(parent);
	int type=nextItemType(item);
	if(type<0)
	{
		return false;
	}
	return !item->hasDataPopulated(type);
}

void views::tagItemModel::fetchMore(const QModelIndex& parent)
{
// 	return ;
	tagItem* item=itemFromIndex(parent);
	int type=nextItemType(item);
	if(type<0)
	{
		return ;
	}
	item->populate(type);
	connect(item,SIGNAL(needUpdate(int) ),this,SLOT(updateData(int) ) );
	beginInsertRows(parent, 0, item->size(type)-1);
	endInsertRows ();
}

bool views::tagItemModel::hasChildren(const QModelIndex& parent) const
{
	tagItem* item=itemFromIndex(parent);
	int type=nextItemType(item);
	
	if(type<0)
	{
		return false;
	}
	
	return true;
}


int views::tagItemModel::nextItemType(views::tagItem* item) const
{
	int k=-1;
	while(item!=0)
	{
		item=item->parentItem();
		k++;
	}
	if(k>=_tags.size())
	{
		return -1;
	}
	return _tags[k];
}

void views::tagItemModel::updateData(int t)
{
    
	tagItem *item=static_cast<tagItem*>(sender() );
	
	int nextType=nextItemType(item);
	        
	if(nextType==t)
	{
            qDebug()<<item->data()<<" "<<t;
		QModelIndex parent;
		tagItem *parentItem;
		if(item==head)
		{
                    parent=QModelIndex();
		}
		else
                {
                    parentItem=item->parentItem();
                    if(parentItem==head)
                    {
                        parent=QModelIndex();
                    }
                    else
                    {
                        parent=createIndex(0,0,parentItem );
                    }
                }
		
		beginRemoveRows(parent, 0, item->size(t)-1);                
		endRemoveRows();
		item->populate(t,true);
		beginInsertRows(parent, 0, item->size(t)-1);
		endInsertRows ();
	}
}
