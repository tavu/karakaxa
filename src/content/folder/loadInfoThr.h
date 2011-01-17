#ifndef LOADINFOTHR_H
#define LOADINFOTHR_H

#include <QThread>
#include<QLinkedList>
#include<QString>
#include<player.h>

class loadInfoThr :public QThread
{
  Q_OBJECT
  public:
      loadInfoThr(QObject *parent=0);
      QLinkedList<QString> fileList;
      QLinkedList<QString>::iterator iter;      
      void updateTracks();
  protected:
      void run();
      
  public slots:
      void cleanup();
      
      
      
};
#endif