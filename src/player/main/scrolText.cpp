#include"scrolText.h"
#include<QPainter>
#include<QDebug>

#define SPACE 10

scrolText::scrolText(QString s,QWidget *parent)
    :QWidget(parent),
    _opacity(1)
{
    setText(s);
    
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}
scrolText::scrolText(QWidget *parent)
        :QWidget(parent),
        _opacity(1)
{
   setText(QString());
}

void scrolText::setText(QString s)
{
    _text=s;
    int w=fontMetrics().size( Qt::TextSingleLine,_text).width() + 3;
    int h=fontMetrics().height();
    //give some extra space
    hint.setWidth(w);
    hint.setHeight(h);
    updateGeometry ();
    update();
}

void scrolText::setTextSize(int s)
{
    QFont f=font();
    f.setPixelSize(s);
    setFont(f);
}

int scrolText::textSize()
{
    return font().pixelSize();
}


QString scrolText::text()
{
    return _text;
}

void scrolText::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setOpacity(_opacity);

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
