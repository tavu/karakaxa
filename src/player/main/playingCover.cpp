#include"playingCover.h"
#include<engine/engine.h>
playingCover::playingCover( QWidget* parent ) : coverWidget ( parent )
{
}

void playingCover::mouseReleaseEvent ( QMouseEvent* event )
{
    core::engine()->playPause();
    QWidget::mouseReleaseEvent ( event );
}

void playingCover::paintEvent ( QPaintEvent * e)
{
    views::coverWidget::paintEvent(e);
    
    QPainter painter(this);
    
    
    QRect r=rect();
    int h=r.height()/3;
    int w=r.width()/3;
    
    QPoint p=r.topLeft();    
    p.setX(p.x()+w);
    p.setY(p.y()+h);
    r.moveTopLeft(p);
    r.setWidth(w);
    r.setHeight(h);
    
    QPen pen(Qt::white);
    pen.setWidth(3);
    painter.setPen(pen);
    
    if(underMouse() )
    {
        painter.setOpacity(0.5);
    }
    else
    {
        painter.setOpacity(0.7);
    }
    
    painter.drawLine(r.topLeft(),r.bottomLeft() );
    painter.drawLine(r.topRight(),r.bottomRight() );
}
