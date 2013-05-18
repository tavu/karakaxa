#include"coverWidget.h"
#include<QDebug>
#include <QLayout>
#include <QVBoxLayout>
#define DEFAULT "data/album.png"
#include"../decoration/decoration.h"
views::coverWidget::coverWidget(QString s ,QWidget * parent, Qt::WindowFlags f  )
        :QFrame(parent,f)
{

//     setSizePolicy(QSizePolicy::Maximum);
    setCover(s);  
}

views::coverWidget::coverWidget(QWidget * parent, Qt::WindowFlags f  )
        :QFrame(parent,f)
{

//     setSizePolicy(QSizePolicy::Maximum);
    setCover(QString());  
}

void views::coverWidget::setSize(QSize s)
{
    setSize(s.width(),s.height() );
}

void views::coverWidget::setSize(int w,int h)
{
    if (!pic.isNull() )
    {
   
        picScaled=pic.scaled(w-2,h-2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);    
    }
    setFixedSize(w,h);
}

void views::coverWidget::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect r=QRect(rect().topLeft(),picScaled.size());
    
    QRect shadowR=r;
    QPoint p=r.topLeft();    
    p.setX(p.x()+2);
    p.setY(p.y()+2);
    shadowR.moveTopLeft(p);
    QPainterPath shadowPath;
    shadowPath.addRoundedRect(shadowR,1,1);
    
    painter.setOpacity(0.5);
    painter.fillPath(shadowPath,Qt::black);
    
    painter.setOpacity(1);    
    painter.drawPixmap(r, picScaled);
}

void views::coverWidget::setCover(QString s)
{

    if (s.isEmpty() )
    {
        pic=views::decor->albumPic();
        art=QString();
    }
    else
    {
        pic.load(s);
        art=s;
        if (pic.isNull() )
        {
            pic=views::decor->albumPic();
            art=QString();
        }
        
    }

    if(!pic.isNull() )
    {
        picScaled=pic.scaled(width()-2,height()-2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        update();
    }
}

QString views::coverWidget::cover()
{
    return art;
}

QSize views::coverWidget::sizeHint () const
{
    return QSize(originalWidth,originalHeight);
}

void views::coverWidget::setHeight(int h)
{        
    picScaled=pic.scaledToHeight(h-2,Qt::SmoothTransformation);
    setFixedHeight(h);
    setFixedWidth(picScaled.width()+2);
}

const int views::coverWidget::originalWidth=156;
const int views::coverWidget::originalHeight=137;
