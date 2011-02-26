#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H
#include<QListWidget>
class albumWidget :public QListView
{
    Q_OBJECT
public:
    albumWidget(QWidget *parent=0);
    QSize sizeHint () const;
public slots:
    void scrollR();
    void scrollL();    

protected:
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent* event);
// 	  virtual void paintEvent ( QPaintEvent * e ) ;
};

#endif
