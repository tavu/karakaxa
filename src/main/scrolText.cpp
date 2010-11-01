#include"scrolText.h"
#include<QPainter>
scrolText::scrolText(QString s,QWidget *parent)
        :QWidget(parent),
        _text(s)
{

}
scrolText::scrolText(QWidget *parent)
        :QWidget(parent)
{

}

void scrolText::setText(QString s)
{
    _text=s;
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

    painter.drawText(rect(),Qt::AlignLeft|Qt::TextSingleLine,_text);

}

QSize scrolText::sizeHint()
{
    QFontMetrics f(font);
    return f.size(Qt::TextSingleLine,_text);
}

void scrolText::setBold(bool b)
{
    font.setBold(b);
}
