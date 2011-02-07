#include"coverWidget.h"
#include<QDebug>
#include <QLayout>
#include <QVBoxLayout>
#define DEFAULT "data/album.png"
player::coverWidget::coverWidget(QString s ,QWidget * parent, Qt::WindowFlags f  )
        :QFrame(parent,f),
        fixedSize(150,170)
//         fixedSize(90,110)
{
//      setFixedSize(90,100 );
    label=new QLabel(this);
    setCover(s);
    QVBoxLayout *l=new QVBoxLayout(this);
//     l->addStretch();
    l->addWidget(label);
    l->addStretch();
    l->setContentsMargins(0,0,0,0);
    setLayout(l);
  
}

player::coverWidget::coverWidget(QWidget * parent, Qt::WindowFlags f  )
        :QFrame(parent,f),
        fixedSize(150,170)
{
    label=new QLabel(this);
    setCover();
    QVBoxLayout *l=new QVBoxLayout(this);
    l->addWidget(label);
    l->addStretch();
    setLayout(l);
}

void player::coverWidget::setSize(QSize s)
{
    fixedSize=s;
    if (pic.isNull() )
    {
        return ;
    }

    picScaled=pic.scaled(s,Qt::KeepAspectRatio,Qt::SmoothTransformation);    
    label->setPixmap(picScaled);
    updateGeometry ();
//     setFixedSize(picScaled.size() );
}

void player::coverWidget::setSize(int x,int y)
{
    QSize s(x,y);
    setSize(s);
}

// void player::coverWidget::paintEvent(QPaintEvent *e)
// {
//       QFrame::paintEvent(e);
// //     QPainter p(this);
// //     p.setRenderHint(QPainter::Antialiasing, true);
// //     p.drawPixmap(QRect(0,0,fixedSize.width(),fixedSize.height()), picScaled);
// }

QSize player::coverWidget::size()
{
    return fixedSize;
}

void player::coverWidget::setCover(QString s)
{

    if (s.isEmpty() )
    {
        pic.load(DEFAULT);
//   	  pic=pic.scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }
    else
    {
        pic.load(s);

        if (pic.isNull() )
        {
            pic.load(DEFAULT);

            if (pic.isNull() )
            {
                return ;
            }
        }
        art=s;
    }

    picScaled=pic.scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    label->setPixmap(picScaled);
//      label.load
//     repaint();
}

QString player::coverWidget::cover()
{
    return art;
}

QSize	player::coverWidget::sizeHint () const
{
    return QFrame::sizeHint();
//     return fixedSize;
}