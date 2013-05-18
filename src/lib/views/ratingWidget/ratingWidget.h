#ifndef STARWIDGET_H
#define STARWIDGET_H
// #include"playerNamespace.h"
// #include"../../files/tagsTable.h"
#include"kratingpainter.h"
#include<QWidget>
//#include"../editors/tagEditor.h"
namespace views
{
class ratingWidget :public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rating READ rating WRITE setRating USER true NOTIFY ratingChanged)
    public:
        ratingWidget(QWidget *parent=0);
        void setRating(int s)
        {
            _rating=s;
            hoverRating=s;
            update();
        }

        int rating()
        {
            return _rating;
        }

        QSize sizeHint() const;
        void setAlignment( Qt::Alignment align );
        void setPixmapSize( int size );

        int spacing() const
        {
            return ratingPainter.spacing();
        }

        void setSpacing( int s )
        {
            ratingPainter.setSpacing( s );
            update();
        }
      
        void setBlack(bool b);
        
        bool isBlack();
      
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
      bool _black;

  signals:
    void ratingChanged(int);
};
};


#endif