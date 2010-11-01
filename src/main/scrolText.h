#ifndef SCROLETEXT_H
#define SCROLETEXT_H
#include<QWidget>
#include<QString>

class scrolText :public QWidget
{
    Q_OBJECT
public:
    scrolText(QString s,QWidget *parent=0);
    scrolText(QWidget *parent=0);
    inline QString text();

    QSize sizeHint();
    void setBold(bool);
private:
    QString _text;
    QFont font;
    void paintEvent(QPaintEvent *event);

public slots:
    void setText(QString s);

};

#endif
