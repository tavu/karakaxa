#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include<QDirIterator>
#include<QSqlQuery>
#include<QFileInfoList>
#include"libraryImporter.h"
#include<QThread>
#include <player.h>
#include<QDir>

class scanTread :public  QThread//, public QObject
{
    Q_OBJECT
public:
    scanTread();

    int importedItemNum();
    inline bool isStoped()
    {
        return stopped;
    }
    inline int importedNum()
    {
        return filesImported;
    }

protected:
    void run();

private:
    libraryImporter importer;

    bool scanFolder(QDir dir);
// 	  void import(QString file);


    void findItemN(QString);
    int itemNumber;
    int num;
    int filesImported;
    bool stopped;
//      public slots:
// 	  void start();

signals:
// 	  void print(const QString);
    void done(int);
    void itemsNum(const int);
    void imported(const int);
    void canceled(int);
    void error(QString);
// 	  void item(const int);
public slots:
    void stop();
};

#endif
