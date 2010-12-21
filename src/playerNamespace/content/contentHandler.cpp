#include"contentHandler.h"
#include<QModelIndex>
#include<QHBoxLayout>
#include<QFont>

#include<QDebug>

#define MAX_HS 20
player::contentHandler::contentHandler(QTreeWidget *tree , QStackedWidget *stack)
        :QObject()
{
    this->tree=tree;
    this->stack=stack;
    connect( tree, SIGNAL( activated ( const QModelIndex & ) ) ,this, SLOT( itemChanger (const QModelIndex &) ) );

    QFont f=item.font(0);

    f.setPixelSize(14);
//      f.setBold(true);
    item.setFont(0,f);
}

abstractContent* player::contentHandler::content(const QModelIndex &index) const
{
    abstractContent *parent;
    QModelIndex parentItem=index.parent();

    if (parentItem.isValid() )
    {
        parent=contentList.at(parentItem.row() );
    }
    else
    {
        parent=contentList.at(index.row() );
    }
    return parent;
}

bool player::contentHandler::isActive(QWidget *w)
{
    qDebug()<<w;
      qDebug()<<stack->currentWidget();
    if(w==stack->currentWidget() )
    {
      ;
      return true;
    }
    
    return false;
}


void player::contentHandler::itemChanger(const QModelIndex &index)
{
    abstractContent *parent;
    QModelIndex parentItem=index.parent();

    if (parentItem.isValid() )
    {
        parent=contentList.at(parentItem.row() );
        stack->setCurrentWidget(parent);
        parent->update(index.row() );
    }
    else
    {
        parent=contentList.at(index.row() );
        stack->setCurrentWidget(parent);
	parent->update(-1);
    }

    history.append(parent);
    if (history.size()>MAX_HS)
    {
        history.removeLast();
    }
}

void player::contentHandler::addContent(abstractContent *content, bool activate)
{
    QTreeWidgetItem *i=content->item();
    contentList.append(content);

    stack->addWidget(content);
    tree->addTopLevelItem(i);

    if (activate)
    {
        tree->setCurrentItem(i);
        stack->setCurrentWidget(content);
    }
}

void player::contentHandler::removeContent(abstractContent *content)
{
    history.removeAll(content);
    int pos=contentList.indexOf(content);
    if (stack->currentWidget()==content)
    {
        QTreeWidgetItem *item;
	abstractContent *c;
        if (! history.isEmpty() )
        {
            item=tree->itemAt(contentList.indexOf(history.last()),0);
	    c=history.last();
        }
        else
        {
            item=tree->itemAt(0,0 );
	    c=contentList.at(0);
        }
        tree->setCurrentItem(item);
        stack->setCurrentWidget(c);
	c->update(-1);
    }

    tree->takeTopLevelItem(pos);
    contentList.removeAt(pos);
    content->deleteLater();
}

void player::contentHandler::addWidget(QWidget *w, bool activate)
{
    genericContent *g=new genericContent(w);
    addContent(g,activate);

}

//=================genericContent================
player::contentHandler::genericContent::genericContent(QWidget *parent)
        :abstractContent()
{
    widget=parent;
    QHBoxLayout *hlayout = new QHBoxLayout();

    hlayout->addWidget(widget);
    this->setLayout(hlayout);
}

QString player::contentHandler::genericContent::genericContent::name() const
{
    if ( widget->windowTitle().isEmpty() )
        return "Unnamed";

    return widget->windowTitle();
}
