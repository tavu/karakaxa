#include"artistWidget.h"

artistWidget::artistWidget(QWidget *parent)
        :QListView(parent)
{
    artistM=new artistModel(this);

    artistM->setQuery( player::db.artist() );
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
