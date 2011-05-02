#include"scrolText.h"
#include<QPainter>
#include<QDebug>

#define SPACE 10

scrolText::scrolText(QString s,QWidget *parent)
    :QWidget(parent),
    _text(s),
    empyText(true)
{
    _text=_text.simplified();
    
    if(_text.isEmpty())
    {
	_text=tr("Unknown");
    }
    QFontMetrics f(font);
    sHint=f.size(Qt::TextSingleLine,_text);
    sHint.setWidth(sHint.width()+SPACE );
    
}
scrolText::scrolText(QWidget *parent)
        :QWidget(parent)
{
    _text=tr("Unknown");
    QFontMetrics f(font);
    sHint=f.size(Qt::TextSingleLine,_text);
    sHint.setWidth(sHint.width()+SPACE );
//     single=f.size(Qt::TextSingleLine,"A");
//     sHint=single;
}

void scrolText::setText(QString s)
{
    s=s.simplified();
    _text=s;
    QFontMetrics f(font);    
    if(_text.isEmpty())
    {
	_text=tr("Unknown");
	empyText=true;
    }
    else
    {
	empyText=false;
    }
    sHint=f.size(Qt::TextSingleLine,_text);
    sHint.setWidth(sHint.width()+SPACE );
    updateGeometry();
    repaint();
}

inline QString scrolText::text()
{
    return _text;
}

void scrolText::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont (font);
    
    if(empyText)
    {
 	painter.setOpacity(0.5);
    }
//     qDebug()<<"text "<<_text;
    QRect r=rect();
    r.setWidth(r.width()-3);
    painter.drawText(r,Qt::AlignLeft|Qt::AlignVCenter|Qt::TextSingleLine,_text);

}

QSize scrolText::sizeHint() const
{
//     return QSize(100,10);
    return sHint;
}

void scrolText::setBold(bool b)
{
    font.setBold(b);
}
