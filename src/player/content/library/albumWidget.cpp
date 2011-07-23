#include"albumWidget.h"
#include<QWheelEvent>
#include<QScrollBar>
#include<QDebug>
#include "albumModel.h"
albumWidget::albumWidget(QWidget *parent)
        :QListView(parent)
{
//     setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
// 	setResizeMode(QListView::Adjust);
	setSpacing(0);
 	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//     setWindowOpacity(0);
}

void albumWidget::setModel(albumModel *m)
{
    QListView::setModel(m);
//     connect(model(),SIGNAL(modelReset() ),this,SLOT(updateEditors() ) );
}


void albumWidget::wheelEvent(QWheelEvent *event)
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-event->delta());
    if(event->delta() >0 )
    {
	emit scrolledR();
    }
    else
    {
      emit scrolledL();
    }
    event->accept();
}

void albumWidget::scrollR()
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()+170);
//     emit scrolledR();
}

void albumWidget::scrollL()
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-170);
}

QSize albumWidget::sizeHint () const
{
    return QSize(1000,170);
}

void albumWidget::resizeEvent(QResizeEvent* event)
{    
    QSize viewS=viewport()->rect().size();
    QSize s=viewport()->rect().size();;

    s.setHeight(s.height());
    s.setWidth(s.height()-10);
    
    albumModel *m=static_cast<albumModel*>(model() );
    m->resize(s);
        
    QListView::resizeEvent(event);
  
    if(horizontalScrollBar()->maximum()==0 )
    {
	   horizontalScrollBar()->hide();
    }
    else
    {
	   horizontalScrollBar()->show();
    }
}

void albumWidget::updateEditors()
{
    for(int i=0;i<model()->rowCount();i++)
    {
	   openPersistentEditor(model()->index(i,0) );
    }
}

