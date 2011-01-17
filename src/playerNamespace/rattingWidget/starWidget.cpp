#include"starWidget.h"
#include<KIcon>
#include<KIconEffect>
#include<QPainter>
#include<QMouseEvent>

/*
    Most of this code is from amarok.
*/

player::starWidget::starWidget(QWidget *parent)
    :QWidget(parent),
    _rating(0),
    hoverRating(-1),
    pixSize(20)
{
    setMouseTracking(true);
}

void player::starWidget::paintEvent(QPaintEvent *event)
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

QSize player::starWidget::sizeHint() const
{
//     return QSize(10,20);
    int numPix =ratingPainter.maxRating();    
    
    QSize pSize( pixSize*numPix + spacing()*(numPix-1) ,pixSize);
    return pSize;
    
}

void player::starWidget::mouseMoveEvent ( QMouseEvent * e )  
{
    QRect rect( contentsRect().topLeft().x(), contentsRect().topLeft().y(),
                    contentsRect().width(), contentsRect().height() );
    hoverRating = ratingPainter.ratingFromPosition( rect, QPoint( e->pos().x(), e->pos().y() ) );

    update();
}

void player::starWidget::mousePressEvent( QMouseEvent *e )
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

void player::starWidget::setPixmapSize( int size )
{
    pixSize = size;
    updateGeometry();
}

void player::starWidget::setAlignment( Qt::Alignment align )
{
    ratingPainter.setAlignment( align );
    update();
}

void player::starWidget::leaveEvent( QEvent *e )
{
    Q_UNUSED(e);
    hoverRating = -1;
    update();
}