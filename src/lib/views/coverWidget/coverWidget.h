#ifndef COVERWIDGET_H
#define COVERWIDGET_H

#include<QFrame>
#include<QPainter>
// #include"playerNamespace.h"
#include<QLabel>

namespace views
{
class coverWidget :public QFrame
{
    public:
        coverWidget ( QString s,QWidget * parent = 0, Qt::WindowFlags f = 0 );
        coverWidget ( QWidget * parent = 0, Qt::WindowFlags f = 0 );
        
        QSize sizeHint() const;
        
        void setSize ( QSize s );
        void setSize ( int w, int h );
                
        void setHeight ( int h );
        void setWidth  ( int w );
        
        QString cover();
        void setCover ( QString s=QString() );
        

    protected:
        QPixmap pic;
        QPixmap picScaled;
        QString art;

        void paintEvent ( QPaintEvent * );
        
        static const int originalWidth;
        static const int originalHeight;
};

};

#endif
