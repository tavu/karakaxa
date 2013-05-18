#ifndef SCROLETEXT_H
#define SCROLETEXT_H
#include<QWidget>
#include<QString>
#include<QPainter>

class scrolText :public QWidget
{
    Q_OBJECT
public:
    scrolText(QString s,QWidget *parent=0);
    scrolText(QWidget *parent=0);
    QString text();
    void setOpacity(qreal p)
    {
        _opacity=p;
    }
    qreal opacity()
    {
        return _opacity;
    }

    QSize sizeHint() const;
    void setBold(bool);
    inline bool isBold();
    void setTextSize(int s);
    int textSize();
private:
    QString _text;
    void paintEvent(QPaintEvent *event);
    QSize hint;
    qreal _opacity;
    
public slots:
    void setText(QString s);

};

#endif
