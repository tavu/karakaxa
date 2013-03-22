#include"configureContent.h"
#include<QVBoxLayout>
#include<QLabel>
#include <QPushButton>
#include<QHBoxLayout>
#include <QGridLayout>
#include<QProgressBar>
#include<QLineEdit>
#include<KIcon>
#include <database.h>
#include<dbJobs/rescanJob.h>
#include<libraryFolder.h>

using namespace core;
using namespace database;
configureContent::configureContent ( QWidget *parent )
    :abstractContent ( parent )
{
    QLabel *l=new QLabel ( this );

    l->setText ( "Player Configuration" );
    QFont font=l->font();
    font.setBold ( true );
    font.setPointSize ( 13 );
    l->setFont ( font );

    QVBoxLayout *layout = new QVBoxLayout();
    libconfInit();

    rememberPl=new QCheckBox ( "remember playlist on exit",this );
    rememberPl->setChecked ( npList()->rememberPlaylist() );
    layout->addWidget ( l );
    layout->addWidget ( groupB );
    layout->addWidget ( rememberPl );
    layout->addStretch();

    layout->setContentsMargins ( 10,10,10,10 );
    setLayout ( layout );

    connect ( rememberPl,SIGNAL ( stateChanged ( int ) ),this,SLOT ( rememberPlSlot ( int ) ) );
    connect ( db(),SIGNAL ( newJob ( database::dbJobP ) ),this,SLOT ( scanButtonActivate ( database::dbJobP ) ) );
}

void configureContent::scanButtonActivate ( database::dbJobP job )
{
    if ( job.isNull() )
    {
        scanB->setDisabled ( false );
        updateB->setDisabled ( false );
        addFolder->setDisabled ( false );
        removeFolder->setDisabled ( false );
    }
    else
    {
        scanB->setDisabled ( true );
        updateB->setDisabled ( true );
        addFolder->setDisabled ( true );
        removeFolder->setDisabled ( true );
    }
}


QString configureContent::name() const
{
    return QObject::tr ( "Config" );
}

void configureContent::rememberPlSlot ( int state )
{
    if ( state==Qt::Checked )
    {
        npList()->setRememberPlaylist ( true );
    }
    else
    {
        npList()->setRememberPlaylist ( false );
    }
}


void configureContent::libconfInit()
{
    groupB=new QGroupBox ( this );
    groupB->setTitle ( tr ( "Library" ) );
    listV=new QListView ( this );
    model=new QStringListModel ( this );

    libraryFolder lf;
    model->setStringList ( lf.libraryFolders() );

    listV->setModel ( model );
    listV->setFixedHeight ( 100 );

    addFolder=new QPushButton ( KIcon ( "list-add" ),tr ( "Add Folder" ),this );
    removeFolder=new QPushButton ( KIcon ( "list-remove" ),tr ( "Remove Folder" ),this );
    scanB=new QPushButton ( tr ( "Scan" ),this );
    scanB->setFixedWidth ( 100 );
    updateB=new QPushButton ( tr ( "Update" ),this );
    updateB->setFixedWidth ( 100 );

    QGridLayout *gl=new QGridLayout ( groupB );
    gl->addWidget ( addFolder,1,0 );
    gl->addWidget ( removeFolder,2,0 );
    gl->addWidget ( listV,0,1,3,1 );

    gl->setRowMinimumHeight ( 4,45 );

    QHBoxLayout *l=new QHBoxLayout();
    l->setContentsMargins ( 0,0,0,0 );
    l->addWidget ( scanB );
    l->addWidget ( updateB );

    gl->addLayout ( l,4,0,1,3,Qt::AlignLeft );

    groupB->setLayout ( gl );

    l->setContentsMargins ( 0,10,0,0 );

    connect ( scanB,SIGNAL ( clicked() ),database::db(),SLOT ( rescan() ) );
    connect ( updateB,SIGNAL ( clicked() ),database::db(),SLOT ( update() ) );
    connect ( addFolder,SIGNAL ( clicked() ),this,SLOT ( addLibraryFolder() ) );
    connect ( removeFolder,SIGNAL ( clicked() ),this,SLOT ( removeLibraryFolder() ) );
}


void configureContent::addLibraryFolder()
{
    QFileDialog *dialog=new QFileDialog ( this );
    dialog->setFileMode ( QFileDialog::Directory );
    dialog->setOption ( QFileDialog::ShowDirsOnly );
    dialog->exec();

    QStringList l=dialog->selectedFiles ();

    if ( l.isEmpty() )
    {
        return;
    }

    libraryFolder lf;
    lf.addLibraryFolder ( l.at ( 0 ) );
    model->setStringList ( lf.libraryFolders() );
}

void configureContent::removeLibraryFolder()
{
    libraryFolder lf;
    lf.removeLibraryFolder ( listV->currentIndex().data().toString() );
    model->setStringList ( lf.libraryFolders() );
}

