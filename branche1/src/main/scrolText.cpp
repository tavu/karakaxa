#include"scrolText.h"
#include<QPainter>
#include<QDebug>
scrolText::scrolText(QString s,QWidget *parent)
    :QWidget(parent),
    _text(s)    
{
    QFontMetrics f(font);
    if(_text.isEmpty())
    {
	sHint=f.size(Qt::TextSingleLine,"A");
    }
    sHint=f.size(Qt::TextSingleLine,_text);
    
}
scrolText::scrolText(QWidget *parent)
        :QWidget(parent)
{
    QFontMetrics f(font);
    sHint=f.size(Qt::TextSingleLine,"A");
}

void scrolText::setText(QString s)
{
    _text=s;
    QFontMetrics f(font);
    if(_text.isEmpty())
    {
	sHint=f.size(Qt::TextSingleLine,"A");
    }
    sHint=f.size(Qt::TextSingleLine,_text);
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
    QRect r=rect();
    r.setWidth(r.width()-3);
    painter.drawText(r,Qt::AlignLeft|Qt::TextSingleLine,_text);

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
