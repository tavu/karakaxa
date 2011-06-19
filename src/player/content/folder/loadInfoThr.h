#ifndef LOADINFOTHR_H
#define LOADINFOTHR_H

#include <QThread>
#include<QLinkedList>
#include<QString>
#include<core.h>

class loadInfoThr :public QThread
{
  Q_OBJECT
  public:
      loadInfoThr(QObject *parent=0);
      QLinkedList<audioFiles::audioFile> fileList;
      QLinkedList<audioFiles::audioFile>::iterator iter;
      void updateTracks();
      
      void cancel()
      {
	  canceled=true;
      }
      
  protected:
      void run();
      bool canceled;
      int  pos;
      
  public slots:
      void cleanup();
      
      
      
};
#endif