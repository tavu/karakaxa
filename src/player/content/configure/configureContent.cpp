#include"configureContent.h"
#include<QVBoxLayout>
#include<QLabel>
#include <QPushButton>
#include<QHBoxLayout>
#include <QGridLayout>
#include<QProgressBar>
#include<QLineEdit>
#include<KIcon>
using namespace core;
configureContent::configureContent(QWidget *parent)
        :abstractContent(parent),
        dbNameS(QObject::tr("database Name:")),
	   dbUserS(QObject::tr("User:")),
	   dbPassS(QObject::tr("password:"))
{
    QLabel *l=new QLabel(this);

    l->setText("Player Configuration");
//     QFont font;
//     font.setBold(true);
//     font.setPointSize(10);
//     l->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout();
    libconfInit();

    rememberPl=new QCheckBox("remember playlist on exit",this);
    rememberPl->setChecked(npList->rememberPlaylist() );
    layout->addWidget(l);
    layout->addWidget(groupB);
    layout->addWidget(rememberPl);
    layout->addStretch();

    layout->setContentsMargins(10,10,10,10);
    setLayout(layout);
    
    connect(rememberPl,SIGNAL(stateChanged(int) ),this,SLOT(rememberPlSlot(int) ) );
}

QString configureContent::name() const
{
    return QObject::tr("Config");
}

void configureContent::rememberPlSlot(int state)
{
    if(state==Qt::Checked)
    {
	   npList->setRememberPlaylist(true);
    }
    else
    {
	   npList->setRememberPlaylist(false);
    }
}


void configureContent::libconfInit()
{
    groupB=new QGroupBox(this);
    groupB->setTitle("Library");
    listV=new QListView(this);
    model=new QStringListModel(db->getLibraryFolders(),this);
    listV->setModel(model);

    QPushButton *addFolder=new QPushButton(KIcon("list-add"),tr("Add Folder"),this);
    QPushButton *removeFolder=new QPushButton(KIcon("list-remove"),tr("Remove Folder"),this);
    scanB=new QPushButton(tr("Scan"),this);
    scanB->setMaximumWidth(100);

    dbNameL = new QLineEdit(db->dataBName(),this);    
    dbUserL = new QLineEdit(db->dataBUser(),this);
    dbPassL = new QLineEdit(db->dataBPass(),this);
    dbPassL->setEchoMode(QLineEdit::Password);
    
     dbNameL->setMinimumWidth(150);
     dbUserL->setMinimumWidth(150);
     dbPassL->setMinimumWidth(150);
    
     DbButtons=new QDialogButtonBox(QDialogButtonBox::Apply|QDialogButtonBox::Cancel,Qt::Horizontal,this);    

     QGridLayout *gl=new QGridLayout(groupB);
     gl->addWidget(&dbNameS,0,0);
     gl->addWidget(dbNameL,0,1);
     gl->addWidget(&dbUserS,1,0);
     gl->addWidget(dbUserL,1,1);
     gl->addWidget(&dbPassS,2,0);
     gl->addWidget(dbPassL,2,1);
     gl->addWidget(DbButtons,3,1);
     
     gl->addWidget(listV,0,2,3,2);
     gl->addWidget(addFolder,3,2);
     gl->addWidget(removeFolder,3,3);
    
     gl->setRowMinimumHeight(4,45);
     gl->addWidget(scanB,5,0);          
     
     gl->setColumnStretch(0,0);     
     gl->setColumnStretch(1,1);     
     gl->setColumnStretch(2,2);     
     gl->setColumnStretch(3,2);
     gl->setRowMinimumHeight(6,15);
    
    
    groupB->setLayout(gl);
    
    
    connect(scanB,SIGNAL(clicked() ),core::db,SLOT(scan()));
    connect(addFolder,SIGNAL(clicked() ),this,SLOT(addLibraryFolder() ) );
    connect(removeFolder,SIGNAL(clicked() ),this,SLOT(removeLibraryFolder() ) );
    connect(DbButtons, SIGNAL(clicked(QAbstractButton* ) ), this, SLOT(DbButtonClicked(QAbstractButton*) ));
}

void configureContent::DbButtonClicked(QAbstractButton *button)
{       
    if (DbButtons->buttonRole(button)==QDialogButtonBox::ApplyRole)
    {
        db->dBConnect(dbNameL->text(),dbUserL->text(),dbPassL->text());
	   db->setUpDb();
    }

    dbNameL->setText(db->dataBName());
    dbUserL->setText(db->dataBUser());
    dbPassL->setText(db->dataBPass());
}

void configureContent::addLibraryFolder()
{
    QFileDialog *dialog=new QFileDialog(this);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setOption(QFileDialog::ShowDirsOnly);
    dialog->exec();
    
    QStringList l=dialog->selectedFiles ();
    if(l.isEmpty())
    {
	return;
    }
    db->addLibraryFolder(l.at(0) );
    model->setStringList(db->getLibraryFolders());
}

void configureContent::removeLibraryFolder()
{    
    db->removeLibraryFolder(listV->currentIndex().data().toString() );    
    model->setStringList(db->getLibraryFolders());
}
