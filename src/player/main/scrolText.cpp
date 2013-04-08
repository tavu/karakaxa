#include"scrolText.h"
#include<QPainter>
#include<QDebug>

#define SPACE 10

scrolText::scrolText(QString s,QWidget *parent)
    :QWidget(parent),
    empyText(true)
{
    setText(s);
    
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}
scrolText::scrolText(QWidget *parent)
        :QWidget(parent)
{
   setText(QString());
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
    hint=fontMetrics().size( Qt::TextSingleLine,_text);
    //give some extra space
    
    hint.setWidth(hint.width()+3);
    updateGeometry ();
    update();
}

inline QString scrolText::text()
{
    return _text;
}

void scrolText::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    
    if(empyText)
    {
        painter.setOpacity(0.5);
    }

    QRect r=rect();
    r.setWidth(r.width()-3);
    QString elideText=fontMetrics().elidedText(_text,Qt::ElideRight,r.width() );
    painter.drawText(r,Qt::AlignLeft|Qt::AlignVCenter|Qt::TextSingleLine|Qt::TextIncludeTrailingSpaces,elideText);
}

QSize scrolText::sizeHint() const
{
    return hint;
}

void scrolText::setBold(bool b)
{
    QFont f=font();
    f.setBold(b);
    setFont(f);
}

bool scrolText::isBold()
{
    return font().bold();
}
