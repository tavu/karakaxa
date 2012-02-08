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
    inline QString text();

    QSize sizeHint() const;
    void setBold(bool);
private:
    QString _text;
    void paintEvent(QPaintEvent *event);
    QSize single;
    bool empyText;
    
public slots:
    void setText(QString s);

};

#endif
