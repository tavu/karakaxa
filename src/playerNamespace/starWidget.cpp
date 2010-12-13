#include"starWidget.h"
#include<KIcon>
#include<KIconEffect>
#include<QPainter>
player::starWidget::starWidget(QWidget *parent)
    :QGraphicsWidget(parent),
    _rating(0),
    showing(true)
{

}

void starWidget::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED( option )
    Q_UNUSED( widget )
    if( showing )
    {
        d->ratingPainter.setEnabled( isEnabled() );
        QRect rect( contentsRect().topLeft().x(), contentsRect().topLeft().y(),
                    contentsRect().width(), contentsRect().height() );
        d->ratingPainter.paint( painter, rect, d->rating, d->hoverRating );
    }

    // HACK: (this works fine, but if a better fix is found, we should replace it)
    // Make sure that the the parent item updates itself correctly on startup.
    // We use a counter variable to prevent infinite recursion.
    if( m_startupUpdates )
    {
        parentItem()->update();
        m_startupUpdates--;
    }
}


void player::starWidget::drawStar(QPainter *painter,QRect rect,int n)
{
    if (n<0||n>10)
    {
        return ;
    }

    KIcon icon("favorites");
    QPixmap activeStar=icon.pixmap(rect.height());

    QPixmap greyStar=KIconEffect().apply( activeStar, KIconEffect::ToGray, 1, QColor(), false );

    int i;
    int X=rect.x();
    for (i=0;i<n;i+=2)
    {		
        painter->drawPixmap(X,rect.y(),activeStar );
	X+=activeStar.width();
    }

    if (i-n==1)
    {
	
        painter->drawPixmap(X ,rect.y() ,activeStar.width()/2, activeStar.height() ,activeStar, 0,0,activeStar.width()/2,activeStar.height() );
        painter->drawPixmap(X+activeStar.width()/2 ,rect.y() ,activeStar.width()/2, activeStar.height() ,greyStar, activeStar.width()/2,0,activeStar.width()/2,activeStar.height() );
	X+=activeStar.width();
        i+=2;
    }
    
    while (i<10)
    {
        painter->drawPixmap(X,rect.y(),greyStar );
	X+=activeStar.width();
        i+=2;
    }
}

QSize player::starWidget::sizeHint() const
{
    return QSize(5, 25);
}