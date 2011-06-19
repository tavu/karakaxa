#include"coverWidget.h"
#include<QDebug>
#include <QLayout>
#include <QVBoxLayout>
#define DEFAULT "data/album.png"
#include"../decoration/decoration.h"
views::coverWidget::coverWidget(QString s ,QWidget * parent, Qt::WindowFlags f  )
        :QFrame(parent,f),
        fixedSize(150,170)
{

//     label=new QLabel(this);
    setCover(s);
//     QVBoxLayout *l=new QVBoxLayout(this);
//     l->addWidget(label);
//     l->addStretch();
//     l->setContentsMargins(0,0,0,0);
//     setLayout(l);
  
}

views::coverWidget::coverWidget(QWidget * parent, Qt::WindowFlags f  )
        :QFrame(parent,f),
        fixedSize(150,170)
{
//     label=new QLabel(this);
    setCover();
//     QVBoxLayout *l=new QVBoxLayout(this);
//     l->addWidget(label);
//     l->addStretch();
//     setLayout(l);
}

void views::coverWidget::setSize(QSize s)
{
//     fixedSize=s;
    if (pic.isNull() )
    {
        return ;
    }

    picSize.setHeight(s.height()-2);
    picSize.setWidth(s.width()-2);
    
    
    picScaled=pic.scaled(picSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);    
    setFixedSize(s);
}

void views::coverWidget::setSize(int w,int h)
{
    QSize s(w,h);
    setSize(s);
}

void views::coverWidget::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect r=QRect(rect().topLeft(),picSize);
    
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

QSize views::coverWidget::size()
{
    return fixedSize;
}

void views::coverWidget::setCover(QString s)
{

    if (s.isEmpty() )
    {
        pic=views::decor->albumPic();
    }
    else
    {
        pic.load(s);
        if (pic.isNull() )
        {
            pic=views::decor->albumPic();

            if (pic.isNull() )
            {
                return ;
            }
        }
        art=s;
    }

    picScaled=pic.scaled(picSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    repaint();
}

QString views::coverWidget::cover()
{
    return art;
}

QSize	views::coverWidget::sizeHint () const
{
    return QFrame::sizeHint();
//     return fixedSize;
}