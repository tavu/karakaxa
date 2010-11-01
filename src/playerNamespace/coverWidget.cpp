#include"coverWidget.h"
#include<QDebug>
#include <QLayout>

player::coverWidget::coverWidget(QString s ,QWidget * parent, Qt::WindowFlags f  )
        :QWidget(parent,f),
        fixedSize(150,170)
{
//      setFixedSize(90,100 );
    setCover(s);
//      qDebug()<<"CC "<<s;

}

player::coverWidget::coverWidget(QWidget * parent, Qt::WindowFlags f  )
        :QWidget(parent,f)
{
    setCover();

}

void player::coverWidget::setSize(QSize s)
{
    if (pic.isNull() )
    {
        return ;
    }

    picScaled=pic.scaled(s,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setFixedSize(picScaled.size() );
    fixedSize=s;
}

void player::coverWidget::setSize(int x,int y)
{
    QSize s(x,y);
    setSize(s);
}

void player::coverWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawPixmap(rect(), picScaled);
}

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

//      label.load
    repaint();
}

QString player::coverWidget::cover()
{
    return art;
}
