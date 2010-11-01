#include"albumWidget.h"
#include<QWheelEvent>
#include<QScrollBar>
#include<QDebug>
albumWidget::albumWidget(QWidget *parent)
        :QListView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowOpacity(0);
}

void albumWidget::wheelEvent(QWheelEvent *event)
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-event->delta());
    event->accept();
}

void albumWidget::scrollR()
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()+170);
}

void albumWidget::scrollL()
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-170);
}

QSize albumWidget::sizeHint () const
{
    return QSize(1000,170);
}

// void albumWidget::paintEvent ( QPaintEvent * e )
// {
// }
