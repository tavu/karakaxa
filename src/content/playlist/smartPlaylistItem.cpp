#include"smartPlaylistItem.h"
#include<QFont>
smartPlaylistItem::smartPlaylistItem(QTreeWidgetItem * parent,Type t)
        :QTreeWidgetItem(parent,t),
        QObject(),
        equalSelector(0),
	lineE(0),
        tagsSpin(0)        
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
         equalSelector(0),
         lineE(0),
         tagsSpin(0)
{
        
      initMatch();
}

void smartPlaylistItem::setXml(QDomElement el)
{
    if (type()==MATCHTYPE)
    {
	QString s=el.attribute("matchtype","all"); 
	
	if(s==QString("all") )
	{
	    tagSelector->setCurrentIndex(0 );	    
	}
	else
	{
	     tagSelector->setCurrentIndex(1);
	}
		
	for(QDomElement e=el.firstChildElement();!e.isNull();e=e.nextSiblingElement() )
	{
	    if(e.tagName()==QString("group") )
	    {
		smartPlaylistItem *item=new smartPlaylistItem(this,MATCHTYPE);
		item->setXml(e);
	    }
	    else if(e.tagName()==QString("field") )
	    {
		smartPlaylistItem *item=new smartPlaylistItem(this,TAGTYPE);
		item->setXml(e);
	    }
	}
    }
    else if (type()==TAGTYPE)
    {	
	int t=el.attribute("tag","0").toInt(0,10);
	tagSelector->setCurrentIndex(t);
	equalSelector->setCurrentIndex(el.attribute("comparison","0").toInt(0,10) );
	int checked=el.attribute("invert","0").toInt(0,10);
	if(checked!=0)
	{	    
	    ch->setCheckState(Qt::Checked);
	}
	else
	{
	    ch->setCheckState(Qt::Unchecked);
	}
 	if(t==YEAR||t==TRACK||t==LENGTH||t==RATING||t==COUNTER||t==BITRATE )
 	{
//  	    tagsSpin =new QSpinBox();
 	    tagsSpin->setValue(el.attribute("value","").toInt() );
//  	    treeWidget()->setItemWidget(this,3,tagsSpin);
 	}
 	else
 	{
 	    lineE->setText(el.attribute("value",""));
//  	    treeWidget()->setItemWidget(this,3,lineE);
 	}
    }
}




void smartPlaylistItem::initTag()
{
    setText(0,tr("Tag") );

    tagSelector=new QComboBox();
    equalSelector=new QComboBox();        
//     lineE=new QLineEdit();
    ch=new QCheckBox();
    ch->setText ("Not");
    treeWidget ()->setItemWidget(this,4,ch);

    QFont f=font(0);
    f.setBold(true);
    setFont(0,f);


//     treeWidget ()->setItemWidget(this,3,lineE);

    for (int i=0;i<FRAME_NUM;i++)
    {
        tagSelector->addItem(tagName( (tagsEnum)i) );
    }
    treeWidget ()->setItemWidget(this,1,tagSelector);

    setupFilde(0);
    treeWidget ()->setItemWidget(this,2,equalSelector);

    connect(tagSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(setupFilde(int) ) );
}

void smartPlaylistItem::initMatch()
{
    QFont f=font(0);
    f.setBold(true);
    setFont(0,f);

    setText(0,tr("Match") );
    tagSelector=new QComboBox();

    tagSelector->addItem(tr("Match all") );
    tagSelector->addItem(tr("Match any") );


    treeWidget ()->setItemWidget(this,1,tagSelector);
}

void smartPlaylistItem::setupFilde(int num)
{
    tagsEnum t=(tagsEnum)num;

    if (t==YEAR||t==TRACK||t==LENGTH||t==RATING||t==COUNTER||t==BITRATE)
    {

        equalSelector->clear();
        equalSelector->addItem(tr("Equal to"),queryGrt::EQUAL);
        equalSelector->addItem(tr("Greater than"),queryGrt::GREATER);
        equalSelector->addItem(tr("Less than"),queryGrt::LESS);

	if(treeWidget()->itemWidget(this,3)!=tagsSpin ||treeWidget()->itemWidget(this,3)==0)
	{
	    tagsSpin=new QSpinBox();
	    treeWidget ()->setItemWidget(this,3,tagsSpin);
	}
	if(t==RATING)
	{
	     tagsSpin->setMaximum(10);
	}
	else
	{
	     tagsSpin->setMaximum(3000);
	}
	if(lineE!=0 )
	{
	    delete lineE;
	    lineE=0;
	}
    }
    else
    {
      	if(treeWidget()->itemWidget(this,3)!=lineE ||treeWidget()->itemWidget(this,3)==0 )
	{
	    lineE=new QLineEdit();
	    treeWidget ()->setItemWidget(this,3,lineE);
	}
	if(tagsSpin!=0)
	{
	    delete tagsSpin;
	    tagsSpin=0;
	}
	
        equalSelector->clear();
        equalSelector->addItem(tr("Equal to"),queryGrt::EQUAL);
        equalSelector->addItem(tr("Contains"),queryGrt::CONTAINS);
        equalSelector->addItem(tr("Starts with"),queryGrt::STARTS);
        equalSelector->addItem(tr("Ends with"),queryGrt::ENDS);
    }

}
/*
QString smartPlaylistItem::getQuery()
{
    queryGrt q;

    if (type()==TAGTYPE)
    {
        tagsEnum t=(tagsEnum)tagSelector->currentIndex ();
        QString s=lineE->text();


        queryGrt::equal eq= (queryGrt::equal) equalSelector->itemData(equalSelector->currentIndex () ).toInt();

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

        if (tagSelector->currentIndex()==0)
        {
            return q.connectAnd(l);
        }
        else
        {
            return q.connectOr(l);
        }
    }
}
*/
QDomElement smartPlaylistItem::xml()
{    
    
    QDomDocument doc;
    QDomElement root;
    bool flag=false;
    if (type()==MATCHTYPE)
    {
        root=doc.createElement("group");
         
	if (tagSelector->currentIndex()==0)
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
// 		qDebug()<<"element "<<el.text();
		root.appendChild(el);
	    }
        }        
    }
    else if (type()==TAGTYPE)
    {
	flag=true;
        root=doc.createElement("field");
	root.setAttribute("tag",tagSelector->currentIndex());
	int eq=equalSelector->itemData(equalSelector->currentIndex()).toInt();
	root.setAttribute("comparison",eq);
	qDebug()<<"EQ "<<eq;
	if(treeWidget()->itemWidget(this,3)==lineE)
	{
	    root.setAttribute("value",lineE->text());
	}
	else
	{
	     root.setAttribute("value",tagsSpin->value());
	}
	root.setAttribute("invert",ch->isChecked());
    
    }
    
    if(flag)
    {
	return root;
    }
    
    return QDomElement();
}





