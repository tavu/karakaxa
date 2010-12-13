#ifndef STARWIDGET_H
#define STARWIDGET_H
#include"playerNamespace.h"
#include<QGraphicsWidget>
namespace player
{
class starWidget :public QGraphicsWidget
{
    public:
	starWidget(QWidget *parent=0);
	inline void setRating(int s)
	{
	    _rating=s;
// 	    repaint();
	}
	
	inline int rating()
	{
	    return _rating;
	}
	static void drawStar(QPainter *painter,QRect rect,int n);  
	QSize sizeHint() const;
 
   protected:
      virtual void mousePressEvent( QGraphicsSceneMouseEvent* e );
      virtual void hoverMoveEvent( QGraphicsSceneHoverEvent* e );
      virtual void hoverEnterEvent( QGraphicsSceneHoverEvent* e );
      virtual void hoverLeaveEvent( QGraphicsSceneHoverEvent* e );
      virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 );
	
  private:
      void paintEvent(QPaintEvent *event);    
      int _rating;
      bool showing;
      
      int rating;
      int hoverRating;
      int pixSize;

      bool showing;
      KRatingPainter ratingPainter;
      
      
};
};


#endif