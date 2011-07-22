#ifndef STARWIDGET_H
#define STARWIDGET_H
// #include"playerNamespace.h"
// #include"../../files/tagsTable.h"
#include"kratingpainter.h"
#include<QWidget>
#include"../editors/tagEditor.h"
namespace views
{
class ratingWidget :public tagEditor
{
    Q_OBJECT
    public:
      ratingWidget(QWidget *parent=0);
      inline void setRating(int s)
      {
		_rating=s;
		hoverRating=s;
		update();
      }
      
	 void setValue(const QVariant& v)
	 {
		setRating(v.toInt() );
	 }
	 
	 QVariant value()
	 {
		return QVariant(rating() );
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