#include"configureContent.h"
#include<QVBoxLayout>
#include<QLabel>
#include <QPushButton>
#include<QHBoxLayout>
#include <QGridLayout>
#include<QProgressBar>
#include<QLineEdit>
configureContent::configureContent(QWidget *parent)
        :abstractContent(parent),
        dbNameS(QObject::tr("database Name:")),
	dbUserS(QObject::tr("User:")),
	dbPassS(QObject::tr("password:"))
{
    QLabel *l=new QLabel(this);
//
    l->setText("Player Configuration");
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    l->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout();
//     sList=db.getLibraryFolders();
    libconfInit();

    chBox=new QCheckBox("remember playlist on exit",this);
    layout->addWidget(l);
    layout->addWidget(groupB);
    layout->addWidget(chBox);
    layout->addStretch();

    layout->setContentsMargins(20,20,50,20);
    setLayout(layout);
}

QString configureContent::name() const
{
    return QObject::tr("Config");
}

void configureContent::libconfInit()
{
    groupB=new QGroupBox(this);
    groupB->setTitle("Library");
    listV=new QListView(this);
    model=new QStringListModel(db.getLibraryFolders(),this);
    listV->setModel(model);

    QPushButton *addFolder=new QPushButton(KIcon("list-add"),tr("Add Folder"),this);
    QPushButton *removeFolder=new QPushButton(KIcon("list-remove"),tr("Remove Folder"),this);
    scanB=new QPushButton(tr("Scan"),this);
    scanB->setFixedWidth(100);

    cancelB=new QPushButton(tr("cancel"));
    cancelB->setFixedWidth(100);
    cancelB->setDisabled(true);

    bar=new QProgressBar(this);
    bar->setFixedWidth(200);
    bar->hide();

    dbNameL = new QLineEdit(db.dataBName(),this);    
    dbUserL = new QLineEdit(db.dataBUser(),this);
    dbPassL = new QLineEdit(db.dataBPass(),this);
    dbPassL->setEchoMode(QLineEdit::Password);
    
    dbNameL->setMinimumWidth(150);
    dbUserL->setMinimumWidth(150);
    dbPassL->setMinimumWidth(150);
    
    DbButtons=new QDialogButtonBox(QDialogButtonBox::Apply|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    
//     QBoxLayout *hlayout=new QBoxLayout(QBoxLayout::LeftToRight);
//     hlayout->addWidget(scanB);
//     hlayout->addWidget(cancelB);
//     hlayout->addStretch();
//     hlayout->addWidget(&info);
//     hlayout->addWidget(bar);
// 
// 
//     QGridLayout *gl=new QGridLayout(groupB);
//     gl->addWidget(&dbNameS,0,0);
//     gl->addWidget(dbNameL,0,1);
//     
//     
//     gl->addWidget(listV,0,2,3,1);
//     gl->addWidget(addFolder,0,3);
//     gl->addWidget(removeFolder,1,3);
//     gl->addLayout(hlayout,4,0);
//     gl->addWidget(&scanInf,4,1);

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
     gl->addWidget(cancelB,5,1);
     gl->addWidget(&scanInf,5,2,Qt::AlignRight);
     gl->addWidget(bar,5,3);
     gl->addWidget(&info,6,3,Qt::AlignRight);
     
     
     
     gl->setColumnStretch(0,0);     
     gl->setColumnStretch(1,1);     
     gl->setColumnStretch(2,2);     
     gl->setColumnStretch(3,2);
     gl->setRowMinimumHeight(6,15);
    
    
    groupB->setLayout(gl);
    
    
    connect(scanB,SIGNAL(clicked() ),this,SLOT(scan()));
    connect(addFolder,SIGNAL(clicked() ),this,SLOT(addLibraryFolder() ) );
    connect(removeFolder,SIGNAL(clicked() ),this,SLOT(removeLibraryFolder() ) );
    connect(DbButtons, SIGNAL(clicked(QAbstractButton* ) ), this, SLOT(DbButtonClicked(QAbstractButton*) ));
}

void configureContent::DbButtonClicked(QAbstractButton *button)
{       
    if (DbButtons->buttonRole(button)==QDialogButtonBox::ApplyRole)
    {
        db.dBConnect(dbNameL->text(),dbUserL->text(),dbPassL->text());
    }

    dbNameL->setText(db.dataBName());
    dbUserL->setText(db.dataBUser());
    dbPassL->setText(db.dataBPass());
}

void configureContent::scan()
{
    bar->setRange(0,0);
    scanB->setDisabled(true);
    cancelB->setDisabled(false);
    bar->setRange(0,0);
    bar->show();
    scanInf.setText("Starting..");
    scThread=new scanTread();

    connect(scThread,SIGNAL(itemsNum(const int)),this,SLOT(prepare(const int)), Qt::QueuedConnection );
    connect(scThread,SIGNAL(imported(const int)),bar,SLOT(setValue(const int)), Qt::QueuedConnection );
    connect(scThread, SIGNAL(finished () ),this,SLOT(scanDone()), Qt::QueuedConnection);
//       connect(scThread, SIGNAL(canceled(int) ),this,SLOT(canceled(int)), Qt::QueuedConnection);
    connect(cancelB, SIGNAL(pressed() ),scThread,SLOT(stop()), Qt::QueuedConnection);


    info.setText("");
    scThread->start();
}

void configureContent::prepare(const int num)
{
    bar->setMaximum(num);
    scanInf.setText("Scanning..");

}

void configureContent::scanDone()
{
    scThread->disconnect();
    scanB->setDisabled(false);
    cancelB->setDisabled(true);

    QString s("Imported %1 files");
    if (scThread->isStoped() )
    {
        scanInf.setText("Canceled");
    }
    else
    {
        bar->setValue(bar->maximum() );
        scanInf.setText("completed");
    }
    info.setText(s.arg(QString::number( scThread->importedNum() ) ) );
    delete scThread;
}

void configureContent::addLibraryFolder()
{
    QFileDialog *dialog=new QFileDialog(this);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setOption(QFileDialog::ShowDirsOnly);
    dialog->exec();
    
    QStringList l=dialog->selectedFiles ();
    qDebug()<<l;
    if(l.isEmpty())
    {
	return;
    }
    db.addLibraryFolder(l.at(0) );
    model->setStringList(db.getLibraryFolders());
}

void configureContent::removeLibraryFolder()
{    
    db.removeLibraryFolder(listV->currentIndex().data().toString() );    
    model->setStringList(db.getLibraryFolders());
}
