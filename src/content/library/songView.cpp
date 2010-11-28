#include"songView.h"
#include"songModel.h"

class editTrack;
songView::songView(QWidget *parent,QString name)
        :myTreeView(parent,name)
{
    createMenu();
    connect(this,SIGNAL(doubleClicked  ( const QModelIndex) ),this,SLOT(play(const QModelIndex) ) );
}

void songView::contextMenuEvent(QContextMenuEvent *e)
{
    if (indexAt(e->pos()).isValid() )
    {
        menu->popup( e->globalPos() );
    }
}

inline void songView::createMenu()
{
    append=new QAction(tr("&Queue track"),this);
    edit=new QAction(tr("Edit"),this);
    editTr=new QAction(tr("&Edit track details"),this);
    delet=new QAction(tr("&Delete"),this);

    menu=new QMenu(this);
    menu->addAction(append);
    menu->addAction(edit);
    menu->addAction(delet);
    menu->addSeparator();
    menu->addAction(editTr);

    connect(editTr,SIGNAL(triggered()),this,SLOT(fileEdit() ) );
}

void songView::fileEdit()
{
    QModelIndexList list=selectedIndexes();

    if (list.isEmpty() )	return;

    const songModel *model=static_cast<const songModel*>(list.at(0).model() );

    foreach(QModelIndex i,list)
    {
        if (i.column()==TITLE)
        {
            player::editTrack(model->url(i.row()).toLocalFile() );
        }
    }
}

void songView::play(const QModelIndex index)
{
    const trackUrl *Model=dynamic_cast<const trackUrl*>(model() );
    
    if(Model==0)
    {
	return;
    }
    
    npList.clear();
    QList <QUrl> urlList;
    
    for (int i=0;i<model()->rowCount();i++)
    {
        npList.insert(i ,nplTrack::getNplTrack(Model->url(i).toLocalFile()) );
    }
    
    engine.play(index.row() );
}

