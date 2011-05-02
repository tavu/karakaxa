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
    
    QSqlQuery q(queryGrt::artist(),db->getDatabase() );
    q.exec();
    artistM->setQuery(q);
    setModel(artistM);
    setUniformItemSizes (true);
    setIconSize(QSize(70,70));
    setWordWrap(true);


    connect(this,SIGNAL(activated ( const QModelIndex) ),this ,SLOT( artistActivated(const QModelIndex&) ) );
}

void artistWidget::artistActivated(const QModelIndex &index)
{
    QString s1=artistM->data(index,Qt::DisplayRole).toString();
    QString s2=artistM->data(index,Qt::UserRole).toString();

    emit(toArtist(s1,s2) );

}

void artistWidget::updateQueries()
{
    QSqlQuery q= artistM->query();
    QSqlQuery nq=QSqlQuery(q.executedQuery(),db->getDatabase() );
    nq.exec();
    artistM->setQuery(nq);
}

void artistWidget::setSearch(const QString &s)
{
    QSqlQuery q(db->getDatabase());
    if(s.isEmpty() )
    {	
	q.prepare(queryGrt::artist() );
    }
    else
    {
	q.prepare(queryGrt::artist(s) );
    }
    
    q.exec();
    artistM->setQuery(q);
}