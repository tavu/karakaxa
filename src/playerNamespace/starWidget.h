#ifndef STARWIDGET_H
#define STARWIDGET_H
#include"playerNamespace.h"
#include<QWidget>
namespace player
{
class starWidget :public QWidget
{
    public:
      starWidget(QWidget *parent=0);
      inline void setRating(int s)
      {
	  _rating=s;
	  repaint();
      }
      
      inline int rating()
      {
	  return _rating;
      }
      static void drawStar(QPainter *painter,QRect rect,int num);  
      QSize sizeHint() const;
  private:
    void paintEvent(QPaintEvent *event);    
    int _rating;
      
};
};


#endif