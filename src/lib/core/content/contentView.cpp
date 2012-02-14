#include"contentView.h"
#include"contentList.h"
#include<QVBoxLayout>
#include<QApplication>
core::contentView::contentView(QObject* parent): QObject(parent)
{
    model=new QStandardItemModel(this);
    stack=new QStackedWidget();
    stack->setMinimumSize(QSize(0,0) );
    _toolBar=new KToolBar( 0,true,false );
    _toolBar->setStyleSheet("QToolBar {background-color: transparent; }");        
    _toolBar->setAutoFillBackground(true);
    
    connect(core::contList,SIGNAL(contentAdded(core::abstractContent*) ),this,SLOT(contentAdded(core::abstractContent* ) ) );
    connect(core::contList,SIGNAL(contentChanged(core::abstractContent*)),this,SLOT(contentActivated(core::abstractContent*)) );
    connect(core::contList,SIGNAL(contentRemoved(core::abstractContent*)),this,SLOT(contentRemoved(core::abstractContent*)) );
}

core::contentView::~contentView()
{
//     delete stack;
//     delete _toolBar;
}


QFrame* core::contentView::mainView() const
{
//     QFrame *f=new QFrame();
//     QVBoxLayout *layout=new QVBoxLayout(f);
//     layout->addWidget(_toolBar);
//     layout->addWidget(stack);
//     f->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    return stack;
}


void core::contentView::activateContFromIndex(const QModelIndex& in)
{
    if(!in.isValid() )
    {
        return;
    }
    
    view->setCurrentIndex(in);
    abstractContent *cont=contentFromIndex(in);
    
    if(view->isExpanded(in) )
    {
	   view->collapse(in);
    }
    else
    {    
	   view->expand(in);
    }

    int r=-1;
    if(in.parent().isValid() )
    {
	r=in.row();
    }    
        
    contList->setCurrentContent(cont,r);
    
}

void core::contentView::contentActivated(core::abstractContent* content)
{
    abstractContent *pre=contList->previousContent();
    if(pre!=0 &&  pre->toolBar!=0)
    {
	contList->previousContent()->toolBarAction->setVisible(false);
    }
    if(content->toolBar!=0 )
    {
 	content->toolBarAction->setVisible(true);
    }

    if(contentFromIndex(view->currentIndex() )!=content )
    {
	view->setCurrentIndex(model->indexFromItem(content->item() ) );
    }
    stack->setCurrentWidget(content);
}

void core::contentView::contentAdded(core::abstractContent* content)
{
    stack->addWidget(content);
    model->appendRow( content->item() );
    
    content->setParent(stack);
//     content->setPalette(stack->palette() );
    content->setMinimumSize(QSize(0,0) );    
    
    if(content->toolBar!=0)
    {
// 	   content->toolBar->setParent(_toolBar);
// 	   content->toolBar->setIconSize(SIZE);
	   content->toolBar->setVisible(false);
	   content->toolBar->setAutoFillBackground(true);
	   
	   QAction *a=_toolBar->addWidget(content->toolBar);
	   content->toolBarAction=a;
	   a->setVisible(false);
	   content->toolBar->setVisible(true);
    }
}

core::abstractContent* core::contentView::contentFromIndex(const QModelIndex& in) const
{
    QModelIndex i=in;
    while(i.parent().isValid())
    {
	i=i.parent();
    }
    return contList->contentFromPos(in.row());
}

void core::contentView::contentRemoved(core::abstractContent* content)
{
    model->removeRow(content->item()->row(),QModelIndex());
    stack->removeWidget(content);
    if(content->toolBar!=0)
    {
      _toolBar->removeAction(content->toolBarAction);
    }    
}



namespace core
{
  contentView *contView;
};