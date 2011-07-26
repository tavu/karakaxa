#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H
#include<QListWidget>
class albumModel;
class albumWidget :public QListView
{
    Q_OBJECT
public:
    albumWidget(QWidget *parent=0);
    QSize sizeHint () const;
public slots:
    void scrollR();
    void scrollL();  
    
    void updateEditors();
    
    void setModel(albumModel *m);
    void updateScroolBar();

protected:
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent* event);
    
  signals:
      void scrolledR();
      void scrolledL();
// 	  virtual void paintEvent ( QPaintEvent * e ) ;
};

#endif
