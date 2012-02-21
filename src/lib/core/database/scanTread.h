#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include<QDirIterator>
#include<QSqlQuery>
#include<QFileInfoList>
#include"libraryImporter.h"
#include<QThread>
#include<QProgressBar>
#include<QDir>
#include <kdirlister.h>
#include "database.h"
#include"album.h"
#include <QLabel>
#include"databaseScanner.h"
namespace core
{
class scanThread :public  databaseScanner//, public QObject
{
    Q_OBJECT
    public:
        scanThread(dbState b,QObject *parent=0);
        ~scanThread();
        int importedItemNum();

        bool isStoped()
        {
            return stopped;
        }
        
        int importedNum()
        {
            return filesImported;
        }

        int step()
        {
            return _step;
        }

        void setStep(int st)
        {
            _step=st;
        }

        QWidget *widget()
        {
            return w;
        }

        void setDirs(const QStringList &l);
        
    protected:
        virtual void     run();
        virtual void     init();
        inline  void     initWidget();
        inline  void     scanAllFolders();
        virtual void     save();
        bool             scanFolder(KUrl url);
        inline  void     findAllItemN();
        void             findItemN(KUrl);

        
        QWidget *w;
        QLabel *label;
        QLinkedList<KUrl> dirs;
        QHash<int,int> allAlbums;
        QLinkedList<QString> errors;        
        bool stopped;
        libraryImporter *importer;
        
    private:        
        int itemNumber;
        int num;
        int filesImported;
                
        QProgressBar *progressBar;
        int _step;
        
    signals:
        void done(int);
        void itemsNum(const int);
        void imported(const int);
        void canceled(int);
        void error(QString);
        // 	  void item(const int);
    public slots:
        void stop();
};

};

#endif
