#include"smartPlaylistCreator.h"
#include<QVBoxLayout>
#include<QAction>
#include<KIcon>

#include<player.h>
#include <QSpinBox>
#include"smartPlaylistDelegate.h"
using namespace::player;
using namespace player;
// using namespace::smartPlaylistItem;
smartPlaylistCreator::smartPlaylistCreator(QWidget *parent)
        :QWidget(parent)
//      query()
{
//      query
    lineE=new QLineEdit(this);
    treeW=new QTreeWidget(this);
    treeW->setColumnCount(5);

//      smartPlaylistDelegate *del=new smartPlaylistDelegate(treeW);


    buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    toolBar=new KToolBar(this);

    QAction *add=new QAction(KIcon("list-add"),tr("&Add"),this);
    QAction *removeAction=new QAction(KIcon("list-remove"),tr("&remove"),this);


    matchAction=new QAction(tr("Match"),this);
    tagAction=new QAction(tr("Tag"),this);

    addMenu=new QMenu(this);
    addMenu->addAction(matchAction);
    addMenu->addAction(tagAction);

    add->setMenu(addMenu);
    toolBar->addAction(add);
    toolBar->addAction(removeAction);

    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *hlayout = new QHBoxLayout();

    QLabel *l=new QLabel(this);
    l->setText("Name");
    hlayout->addWidget(l);
    hlayout->addWidget(lineE);

    layout->addWidget(toolBar);
    layout->addLayout(hlayout);
    layout->addWidget(treeW);
    layout->addWidget(buttons);

    setLayout(layout);

//      QStringList l;
//      l<<tr("Match")<<tr("all");
    QTreeWidgetItem *item=new smartPlaylistItem(treeW);
//      addTopLevelItem

    connect(matchAction, SIGNAL(triggered()), this, SLOT(addMatch()));
    connect(tagAction, SIGNAL(triggered()), this, SLOT(addTag()));
    connect(removeAction, SIGNAL(triggered()), this, SLOT(remove()));

    connect(buttons, SIGNAL(accepted()), this, SLOT(ok()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(cancel()));
}

void smartPlaylistCreator::addMatch()
{
    addItem(smartPlaylistItem::MATCHTYPE);
}

void smartPlaylistCreator::addTag()
{
    addItem(smartPlaylistItem::TAGTYPE);
}

void smartPlaylistCreator::addItem(smartPlaylistItem::Type type)
{
    QTreeWidgetItem *father=treeW->currentItem();

    if (father==0)
    {
        father=treeW->topLevelItem(0);
    }
    else
    {
        while (father->type()==smartPlaylistItem::TAGTYPE)
            father=father->parent();
    }

    QTreeWidgetItem *item =new smartPlaylistItem(father,type );
//      QSpinBox *spin=new QSpinBox(this);
//      treeW->setItemWidget(item,3,spin);
    treeW->expandItem(father);
}

void smartPlaylistCreator::remove()
{
    QTreeWidgetItem *i=treeW->currentItem();

    if (i==0)	return ;

    QTreeWidgetItem *father=i->parent();

    if (father==0)	return ;

    father->removeChild(i);
    delete i;

}

void smartPlaylistCreator::ok()
{
//      close();
    smartPlaylistItem *item=static_cast<smartPlaylistItem*>(treeW->topLevelItem(0) );
    query=item->getQuery();

    queryGrt q;
    query=q.finish(query);
    close();

}

void smartPlaylistCreator::cancel()
{
    close();
}

void smartPlaylistCreator::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent(event);
    emit(closed(query,name()) );
}

QString smartPlaylistCreator::name()
{
    if (lineE->text().isEmpty() )
        return QString(tr("Unnamed") );
    return lineE->text();
}
