#include"ratingWidget.h"
#include<kicon.h>
#include<kiconeffect.h>
#include<QPainter>
#include<QMouseEvent>

/*
    Most of this code is from amarok.
*/

views::ratingWidget::ratingWidget(QWidget *parent)
    :QWidget(parent),
    _rating(0),
    hoverRating(-1),
    pixSize(20)
{
    setMouseTracking(true);
}

void views::ratingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if( true )
    {
        ratingPainter.setEnabled( true );
        QRect rect( contentsRect().topLeft().x(), contentsRect().topLeft().y(),
                    contentsRect().width(), contentsRect().height() );
        ratingPainter.paint( &painter, rect, _rating, hoverRating );
    }
}

QSize views::ratingWidget::sizeHint() const
{
//     return QSize(10,20);
    int numPix =ratingPainter.maxRating();    
    
    QSize pSize( pixSize*numPix + spacing()*(numPix-1) ,pixSize);
    return pSize;
    
}

void views::ratingWidget::mouseMoveEvent ( QMouseEvent * e )  
{
    QRect rect( contentsRect().topLeft().x(), contentsRect().topLeft().y(),
                    contentsRect().width(), contentsRect().height() );
    hoverRating = ratingPainter.ratingFromPosition( rect, QPoint( e->pos().x(), e->pos().y() ) );

    update();
}

void views::ratingWidget::mousePressEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton )
    {
        QRect rect( contentsRect().topLeft().x(), contentsRect().topLeft().y(),
                    contentsRect().width(), contentsRect().height() );
        int ratingFromPos = ratingPainter.ratingFromPosition( rect, QPoint( e->pos().x(), e->pos().y() ) );
        if ( ratingFromPos >= 0 )
        {
            hoverRating = _rating = ratingFromPos;
            update();
            emit ratingChanged( _rating );
        }
    }
}

void views::ratingWidget::setPixmapSize( int size )
{
    pixSize = size;
    updateGeometry();
}

void views::ratingWidget::setAlignment( Qt::Alignment align )
{
    ratingPainter.setAlignment( align );
    update();
}

void views::ratingWidget::leaveEvent( QEvent *e )
{
    Q_UNUSED(e);
    hoverRating = -1;
    update();
}