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
      void updateTracks();
      
      void cancel()
      {
	  canceled=true;
      }
      void addItems(QLinkedList<audioFiles::audioFile> &l);
      
  protected:
          
	 QLinkedList<audioFiles::audioFile> fileList;
      QLinkedList<audioFiles::audioFile>::iterator iter;
      void run();
      bool canceled;
	 QMutex *mutex;
      
  public slots:
      void cleanup();
      
      
      
};
#endif