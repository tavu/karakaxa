#include"smartPlaylistItem.h"
#include<QFont>
smartPlaylistItem::smartPlaylistItem(QTreeWidgetItem * parent,Type t)
        :QTreeWidgetItem(parent,t),
        QObject(),
        spin(0),
        val(0)
{
    if (type()==MATCHTYPE)
    {
        initMatch();
    }
    else if (type()==TAGTYPE)
    {
        initTag();
    }
}

smartPlaylistItem::smartPlaylistItem(QTreeWidget * parent)
        :QTreeWidgetItem(parent,MATCHTYPE),
        QObject(),
        spin(0),
        val(0)
{
    if (type()==MATCHTYPE)
    {
        initMatch();
    }
    else if (type()==TAGTYPE)
    {
        initTag();
    }
}

void smartPlaylistItem::initTag()
{
    setText(0,tr("Tag") );

    box1=new QComboBox();
    box2=new QComboBox();
    lineE=new QLineEdit();
    ch=new QCheckBox();
    ch->setText ("Not");
    treeWidget ()->setItemWidget(this,4,ch);

    QFont f=font(0);
    f.setBold(true);
    setFont(0,f);


    treeWidget ()->setItemWidget(this,3,lineE);

    for (int i=0;i<FRAME_NUM;i++)
    {
        box1->addItem(tagName( (tagsEnum)i) );
    }
    treeWidget ()->setItemWidget(this,1,box1);

    setupFilde(0);
    treeWidget ()->setItemWidget(this,2,box2);

    connect(box1,SIGNAL(currentIndexChanged(int)),this,SLOT(setupFilde(int) ) );
}

void smartPlaylistItem::initMatch()
{
    QFont f=font(0);
    f.setBold(true);
    setFont(0,f);

    setText(0,tr("Match") );
    box1=new QComboBox();

    box1->addItem(tr("Match all") );
    box1->addItem(tr("Match any") );


    treeWidget ()->setItemWidget(this,1,box1);
}

void smartPlaylistItem::setupFilde(int num)
{
    tagsEnum t=(tagsEnum)num;

    if (t==YEAR||t==TRACK||t==LENGTH||t==RATING||t==COUNTER||t==BITRATE)
    {

        box2->clear();
        box2->addItem(tr("Equal to"),queryGrt::EQUAL);
        box2->addItem(tr("Greater than"),queryGrt::GREATER);
        box2->addItem(tr("Less than"),queryGrt::LESS);

        if (val==0)
        {
            val=new validator();
        }

        lineE->clear();
        lineE->setValidator(val);
    }
    else
    {
        box2->clear();
        box2->addItem(tr("Equal to"),queryGrt::EQUAL);
        box2->addItem(tr("Contains"),queryGrt::CONTAINS);
        box2->addItem(tr("Starts with"),queryGrt::STARTS);
        box2->addItem(tr("Ends with"),queryGrt::ENDS);

        lineE->setValidator(0);
    }

}

QValidator::State validator::validate ( QString & input, int & pos ) const
{
    Q_UNUSED(pos);
    bool b;

    input.toInt(&b);

    if (b)
    {
        return QValidator::Acceptable;
    }

    return QValidator::Invalid;
}

QString smartPlaylistItem::getQuery()
{
    queryGrt q;

    if (type()==TAGTYPE)
    {
        tagsEnum t=(tagsEnum)box1->currentIndex ();
        QString s=lineE->text();


        queryGrt::equal eq= (queryGrt::equal) box2->itemData(box2->currentIndex () ).toInt();

        bool n=ch->isChecked();

//         qDebug()<<t<<eq<<s<<n;
        return q.query(t,eq,s,n);
    }
    if (type()==MATCHTYPE)
    {
        QStringList l;

        for (int i=0;i<childCount();i++)
        {
            smartPlaylistItem *item=static_cast<smartPlaylistItem*>(QTreeWidgetItem::child(i) );
            QString s=item->getQuery();
            if (s.isEmpty() )
            {
                qDebug()<<"error creating query";
                return QString();
            }
            l<<s;
        }

        if (box1->currentIndex()==0)
        {
            return q.connectAnd(l);
        }
        else
        {
            return q.connectOr(l);
        }
    }
}

QDomElement smartPlaylistItem::xml()
{    
    
    QDomDocument doc;
    QDomElement root;
    bool flag=false;
    if (type()==MATCHTYPE)
    {
        root=doc.createElement("group");
         
	if (box1->currentIndex()==0)
        {
            root.setAttribute("matchtype","all");
        }
        else
        {
            root.setAttribute("matchtype","any");
        }
        for (int i=0;i<childCount();i++)
        {
            smartPlaylistItem *item=static_cast<smartPlaylistItem*>(QTreeWidgetItem::child(i) );
            QDomElement el=item->xml();
	    //if there is not a valid childre the flag would be false and we gonna return an null element
	    //that could happend for example if there is not any tag field
 	    if(!el.isNull() )
	    {
		flag=true;
		qDebug()<<"element "<<el.text();
		root.appendChild(el);
	    }
        }        
    }
    else if (type()==TAGTYPE)
    {
	flag=true;
        root=doc.createElement("field");
	root.setAttribute("tag",box1->currentIndex());
	root.setAttribute("comparison",box2->currentIndex());
	root.setAttribute("value",lineE->text());
	root.setAttribute("invert",ch->isChecked());
    
    }
    
    if(flag)
    {
	return root;
    }
    
    return QDomElement();
}





