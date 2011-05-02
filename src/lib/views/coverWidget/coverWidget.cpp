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

    label=new QLabel(this);
    setCover(s);
    QVBoxLayout *l=new QVBoxLayout(this);
    l->addWidget(label);
    l->addStretch();
    l->setContentsMargins(0,0,0,0);
    setLayout(l);
  
}

views::coverWidget::coverWidget(QWidget * parent, Qt::WindowFlags f  )
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

void views::coverWidget::setSize(QSize s)
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

void views::coverWidget::setSize(int x,int y)
{
    QSize s(x,y);
    setSize(s);
}

// void views::coverWidget::paintEvent(QPaintEvent *e)
// {
//       QFrame::paintEvent(e);
// //     QPainter p(this);
// //     p.setRenderHint(QPainter::Antialiasing, true);
// //     p.drawPixmap(QRect(0,0,fixedSize.width(),fixedSize.height()), picScaled);
// }

QSize views::coverWidget::size()
{
    return fixedSize;
}

void views::coverWidget::setCover(QString s)
{

    if (s.isEmpty() )
    {
        pic=views::decor->albumPic();
//   	  pic=pic.scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
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

    picScaled=pic.scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    label->setPixmap(picScaled);
//      label.load
//     repaint();
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