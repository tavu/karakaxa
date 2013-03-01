#include"artistWidget.h"
#include"artistDelegate.h"
#include<core.h>
using namespace core;
artistWidget::artistWidget(QWidget *parent)
        :QListView(parent)
{
    artistM=new artistModel(this);
    artistDelegate *del=new artistDelegate(this);
    setItemDelegate(del);
    setModel(artistM);    
    setUniformItemSizes (true);
//     setIconSize(QSize(70,70));
    setWordWrap(true);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//     artistM->update();


    connect(this,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( artistActivated(const QModelIndex&) ) );
}

void artistWidget::artistActivated(const QModelIndex &index)
{
    QString s=artistM->data(index,Qt::UserRole).toString();
//     queryGrt::tagQuery(ARTIST,queryGrt::EQUAL,s2);
    
    

    emit toArtist(s);

}

void artistWidget::setSearch(const QString &s)
{
/*    QSqlQuery q(db->getDatabase());
    if(s.isEmpty() )
    {	
	q.prepare(queryGrt::artist() );
    }
    else
    {
	q.prepare(queryGrt::artist(s) );
    }
    
    q.exec();
    artistM->setQuery(q);*/
}