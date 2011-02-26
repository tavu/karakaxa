#ifndef LOADINFOTHR_H
#define LOADINFOTHR_H

#include <QThread>
#include<QLinkedList>
#include<QString>
#include<player.h>
#include<audioFile.h>
using namespace audioFiles;
class loadInfoThr :public QThread
{
  Q_OBJECT  
  public:
      loadInfoThr(QObject *parent=0);
      inline void cancel()
      {
	canceled=true;
      }

      QLinkedList<audioFile> fileList;      
      void updateTracks();
  protected:
      void run();
      bool canceled;            
      QLinkedList<audioFile>::iterator iter;
      
  public slots:
      void cleanup();
      
      
      
};
#endif