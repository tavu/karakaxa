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
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
scrolText::scrolText(QWidget *parent)
        :QWidget(parent)
{
    _text=tr("Unknown");    
}

void scrolText::setText(QString s)
{
    s=s.simplified();
    _text=s;
    if(_text.isEmpty())
    {
        _text=tr("Unknown");
        empyText=true;
    }
    else
    {
        empyText=false;
    }
    update();
}

inline QString scrolText::text()
{
    return _text;
}

void scrolText::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont (font());
    
    if(empyText)
    {
        painter.setOpacity(0.5);
    }

    QRect r=rect();
    r.setWidth(r.width()-3);
    QString elideText=fontMetrics().elidedText(_text,Qt::ElideRight,rect().width() );
    painter.drawText(r,Qt::AlignLeft|Qt::AlignVCenter|Qt::TextSingleLine|Qt::TextIncludeTrailingSpaces,elideText);
}

QSize scrolText::sizeHint() const
{
    return QSize(100,10);
}

void scrolText::setBold(bool b)
{
    QFont f=font();
    f.setBold(b);
    setFont(f);
}
