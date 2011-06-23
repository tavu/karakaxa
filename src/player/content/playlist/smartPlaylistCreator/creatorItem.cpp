#include"creatorItem.h"
#include<QFont>
#include<core.h>
#include<views.h>
using namespace core;
creatorItem::creatorItem(creatorItem* parent, creatorItem::Type t)
        :QTreeWidgetItem(parent,t),
        QObject(),
        doc(parent->document()),
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

creatorItem::creatorItem(QDomDocument &docum,QTreeWidget * parent)
         :QTreeWidgetItem(parent,MATCHTYPE),
         QObject(),
         doc(docum),
         equalSelector(0),
         lineE(0),
         tagsSpin(0)
{
        
      initMatch();
}

void creatorItem::setXml(QDomElement el)
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
		creatorItem *item=new creatorItem(this,MATCHTYPE);
		item->setXml(e);
	    }
	    else if(e.tagName()==QString("field") )
	    {
		creatorItem *item=new creatorItem(this,TAGTYPE);
		item->setXml(e);
	    }
	}
    }
    else if (type()==TAGTYPE)
    {	
	int t=el.attribute("tag","0").toInt(0,10);
	tagSelector->setCurrentIndex(t);
	
	int eq=el.attribute("comparison","0").toInt(0,10);
	
	for(int i=0;i<queryGrt::LESS;i++)
	{
	    if(equalSelector->itemData(i).toInt()==eq )
	    {
		equalSelector->setCurrentIndex(i);
		break;
	    }
	}
	
// 	equalSelector->setCurrentIndex(el.attribute("comparison","0").toInt(0,10) );
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




void creatorItem::initTag()
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
        tagSelector->addItem(views::tagName( i) );
    }
    treeWidget ()->setItemWidget(this,1,tagSelector);

    setupFilde(0);
    treeWidget ()->setItemWidget(this,2,equalSelector);

    connect(tagSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(setupFilde(int) ) );
}

void creatorItem::initMatch()
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

void creatorItem::setupFilde(int num)
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
QString creatorItem::getQuery()
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
            creatorItem *item=static_cast<creatorItem*>(QTreeWidgetItem::child(i) );
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
QDomElement creatorItem::xml()
{        
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
            creatorItem *item=static_cast<creatorItem*>(QTreeWidgetItem::child(i) );
            QDomElement el=item->xml();
	    //if there is not a valid childre the flag would be false and we gonna return an null element
	    //that could happend for example if there is not any tag field
 	    if(!el.isNull() )
	    {
		flag=true;
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





