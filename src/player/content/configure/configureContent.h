#ifndef CONFIGURECONTENT_H
#define CONFIGURECONTENT_H
#include<QFileDialog>
#include<QListView>
#include <QStringListModel>
#include<QGroupBox>
#include<QLabel>
#include<QProgressBar>
#include <QCheckBox>
#include<QDialogButtonBox>
#include<core.h>
#include<KIcon>
#include<dbJobs/dbJob.h>

class configureContent :public core::abstractContent
{
        Q_OBJECT
    public:
        configureContent ( QWidget *parent=0 );
        QString name() const;

        QIcon icon() const
        {
            return KIcon ( "configure-other" );
        }

    private:
        QFileDialog         *fDialog;
        QListView           *listV;
        QStringListModel    *model;
        QStringList      sList;
        QGroupBox           *groupB;

        QPushButton         *scanB;
        QPushButton         *updateB;
        QCheckBox           *rememberPl;
        QPushButton         *addFolder;
        QPushButton         *removeFolder;


        inline void libconfInit();


    private slots:
        void addLibraryFolder();
        void removeLibraryFolder();
        void rememberPlSlot ( int );
        void scanButtonActivate ( database::dbJobP );
};
#endif
