#ifndef COVERWIDGET_H
#define COVERWIDGET_H

#include<QFrame>
#include<QPainter>
// #include"playerNamespace.h"
#include<QLabel>

namespace views
{
class coverWidget :public QFrame
{
public:
    coverWidget(QString s=QString(), QWidget * parent = 0, Qt::WindowFlags f = 0 );
    coverWidget( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    void setSize(QSize s);
    void setSize(int w, int h);
    QSize size();
    QString cover();
    void setCover(QString s=QString() );
    QSize sizeHint() const;
private:
    QSize picSize;
    QPixmap pic;
    QPixmap picScaled;

    QLabel *label;
    QString art;
    QSize fixedSize;

    void paintEvent(QPaintEvent *);
};

};

#endif
