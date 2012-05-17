#ifndef RESCAN_JOB
#define RESCAN_JOB

#include"dbThrJob.h"
#include"../dbTypes.h"
#include "../database.h"
#include "../album.h"
#include"../libraryImporter.h"

#include<KUrl>
#include<QLabel>
#include<QProgressBar>
#include<QHash>
#include<QLinkedList>
#include<QDir>
#include <kdirlister.h>


namespace database
{

class rescanJob :public dbThrJob
{
    Q_OBJECT
    public:
        rescanJob(dbState b,QObject *parent=0);
        ~rescanJob();

        dbState type()
        {
            return _type;
        }

        int importedItemNum();

        int importedNum()
        {
            return filesImported;
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
        void             findItemN(KUrl dir);



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
        bool canceled;
        dbEventP eventP;
        dbState _type;

    signals:
        void itemsNum(const int);
        void imported(const int);

    public slots:
        void cancel();
//         void error(QString);

};

}
#endif
