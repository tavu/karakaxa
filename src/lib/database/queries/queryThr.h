#ifndef QUERYTHR_H
#define QUERYTHR_H

#include<QThread>
#include<QVector>

#include"../files/audioFiles.h"

#include "database.h"


namespace database
{
class queryThr :public QThread
{
    Q_OBJECT	
    public:	    
      queryThr(QObject *parent):QThread(parent),step(50)
      {}

      void run();
      int step;
      QVector<audioFiles::audioFile> files;	
      QMap<QString ,audioFiles::audioFile> map;

  signals:
    void items(QVector<audioFiles::audioFile> );
	    
};

};
#endif