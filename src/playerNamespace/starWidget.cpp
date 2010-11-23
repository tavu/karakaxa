#include"starWidget.h"
#include<KIcon>
#include<KIconEffect>
#include<QPainter>
player::starWidget::starWidget(QWidget *parent)
    :QWidget(parent),
    _rating(0)
{

}

void player::starWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawStar(&painter,rect(),_rating);
}

void player::starWidget::drawStar(QPainter *painter,QRect rect,int num)
{
    if (num<0||num>255)
    {
        return ;
    }

    int n=num/25;
    if (num%25>0 && n!=10) 	n++;

    KIcon icon("favorites");
    QPixmap activeStar=icon.pixmap(rect.height());

    QPixmap greyStar=KIconEffect().apply( activeStar, KIconEffect::ToGray, 1, QColor(), false );

//     QPixmap halfStar=KIconEffect().apply( activeStar, KIconEffect::ToGray, 0.2, QColor(), false );

//      activeStar=KIconEffect().apply( activeStar, KIconEffect::ToGray, 0.8, QColor(), false );
    int i;
    int X=rect.x();
    for (i=0;i<n;i+=2)
    {		
        painter->drawPixmap(X,rect.y(),activeStar );
	X+=activeStar.width();
// 	if(X>rect.x())	return;
    }

    if (n-i==-1)
    {
//         int x=rect.x()+(i/2)*activeStar.width();	
// 	if(X+activeStar.width()>rect.x())	return;
	
        painter->drawPixmap(X ,rect.y() ,activeStar.width()/2, activeStar.height() ,activeStar, 0,0,activeStar.width()/2,activeStar.height() );
        painter->drawPixmap(X+activeStar.width()/2 ,rect.y() ,activeStar.width()/2, activeStar.height() ,greyStar, activeStar.width()/2,0,activeStar.width()/2,activeStar.height() );
	X+=activeStar.width();
        i+=2;
    }
    
    while (i<10)
    {
        painter->drawPixmap(X,rect.y(),greyStar );
	X+=activeStar.width();
// 	if(X>rect.x())	return;
        i+=2;
    }
}

QSize player::starWidget::sizeHint() const
{
    return QSize(5, 25);
}