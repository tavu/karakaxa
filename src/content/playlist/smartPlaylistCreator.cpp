#include"smartPlaylistCreator.h"
#include<QVBoxLayout>
#include<QAction>
#include<KIcon>

#include<player.h>
#include <QSpinBox>
#include<QPushButton>



using namespace player;
// using namespace::smartPlaylistItem;
smartPlaylistCreator::smartPlaylistCreator(QWidget *parent)
        :QDialog(parent)
{
    init();   
    smartPlaylistItem *item=new smartPlaylistItem(treeW);
}

smartPlaylistCreator::smartPlaylistCreator(smplaylistItem *item,QWidget *parent)
        :QDialog(parent)
{
    init();   
    QDomElement el=item->xml();
    QDomElement e=el.firstChildElement();
    lineE->setText(el.attribute("name") );
    smartPlaylistItem *i=new smartPlaylistItem(treeW);
    i->setXml(e);
    treeW->expandItem(i);

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


smplaylistItem* smartPlaylistCreator::item()
{
    smplaylistItem *ret=0;
    QDomElement el=xml();
    
    if(!el.isNull() )
    {
	ret=new smplaylistItem(name() );
	ret->setXmlElement(el);
    }
    return ret;
}

QString smartPlaylistCreator::name()
{
    if (lineE->text().isEmpty() )
    {
        return QString(tr("Unnamed") );
    }
    return lineE->text();
}

QSize smartPlaylistCreator::sizeHint() const
{
    return QSize(700,600);
}

QDomElement smartPlaylistCreator::xml()
{
    smartPlaylistItem *item=static_cast<smartPlaylistItem*>(treeW->topLevelItem(0) );
    
    QDomElement root,el;
    el=item->xml();
    
    if(!el.isNull() )
    {
      QDomDocument doc;
      root= doc.createElement("smartPlaylist");    
      root.setAttribute("name",name() );
      root.appendChild(el);      
      doc.appendChild(root);

    }          
    
    return root;
}

void smartPlaylistCreator::init()
{
    setWindowTitle(tr("Creating smart Playlist"));
    lineE=new QLineEdit(this);
    treeW=new QTreeWidget(this);
    treeW->setColumnCount(5);


    buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    toolBar=new KToolBar(this);

    QPushButton *add=new QPushButton(KIcon("list-add"),tr("&Add"),this);
    QAction *removeAction=new QAction(KIcon("list-remove"),tr("&remove"),this);


    matchAction=new QAction(tr("Match"),this);
    tagAction=new QAction(tr("Tag"),this);

    addMenu=new QMenu(this);
    addMenu->addAction(matchAction);
    addMenu->addAction(tagAction);

    add->setMenu(addMenu);
    add->setFlat(true);
    
    toolBar->addWidget(add);
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
//      addTopLevelItem

    connect(matchAction, SIGNAL(triggered()), this, SLOT(addMatch()));
    connect(tagAction, SIGNAL(triggered()), this, SLOT(addTag()));
    connect(removeAction, SIGNAL(triggered()), this, SLOT(remove()));

    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
}

