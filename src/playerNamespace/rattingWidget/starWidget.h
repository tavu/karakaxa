#ifndef STARWIDGET_H
#define STARWIDGET_H
#include"playerNamespace.h"
#include"kratingpainter.h"
#include<QWidget>
namespace player
{
class starWidget :public QWidget
{
    Q_OBJECT
    public:
      starWidget(QWidget *parent=0);
      inline void setRating(int s)
      {
	  _rating=s;
	  hoverRating=s;
	  update();
      }
      
      inline int rating()
      {
	  return _rating;
      }
      
      QSize sizeHint() const;
      void setAlignment( Qt::Alignment align );
      void setPixmapSize( int size );
      
      inline int spacing() const
      {
	  return ratingPainter.spacing();
      }
      
      inline void setSpacing( int s )
      {
	  ratingPainter.setSpacing( s );
	  update();
      }
      
      
  protected:
      virtual void mouseMoveEvent ( QMouseEvent * e )  ;
      virtual void mousePressEvent( QMouseEvent *e );
      virtual void leaveEvent( QEvent *e );
//       virtual void enterEvent( QEvent *e );
  private:
      void paintEvent(QPaintEvent *event);    
      int _rating;
      int hoverRating;
      int pixSize;
      KRatingPainter ratingPainter;

  signals:
    void ratingChanged(int);
};
};


#endif