#include"artistWidget.h"

artistWidget::artistWidget(QWidget *parent)
        :QListView(parent)
{
    artistM=new artistModel(this);

    QSqlQuery q(queryGrt::artist(),db.getDatabase() );
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

void artistWidget::setSearch(const QString &s)
{
    QSqlQuery q(db.getDatabase());
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