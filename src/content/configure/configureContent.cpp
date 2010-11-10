#include"configureContent.h"
#include<QVBoxLayout>
#include<QLabel>
#include <QPushButton>
#include<QHBoxLayout>
#include <QGridLayout>
#include<QProgressBar>
configureContent::configureContent(QWidget *parent)
        :abstractContent(parent)
{
    QLabel *l=new QLabel(this);
//
    l->setText("Player Configuration");
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    l->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout();
    sList=db.getLibraryFolders();
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
//      groupB->setFlat(true);

//      QVBoxLayout *gl = new QVBoxLayout(groupB);
// //      groupB->setAlignment(Qt::AlignLeft);
//
    groupB->setTitle("Library Folders");
//
//      QHBoxLayout *hlayout = new QHBoxLayout(groupB);
//      QVBoxLayout *vlayout = new QVBoxLayout();
//
//
    listV=new QListView(this);
    model=new QStringListModel(sList,this);
    listV->setModel(model);
//
//
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
//      vlayout->addWidget(addFolder);
//      vlayout->addWidget(removeFolder);
//      vlayout->addStretch();
//
//      hlayout->addWidget(listV);
//      hlayout->addLayout(layout);
//      gl->setContentsMargins(0,0,0,0);
//
//      groupB->setMaximumHeight(400);
//      groupB->setMaximumSize(400,400);
//      layout->addWidget(l);

//      QHBoxLayout *hlayout = new QHBoxLayout();
    QBoxLayout *hlayout=new QBoxLayout(QBoxLayout::LeftToRight);
    hlayout->addWidget(scanB);
    hlayout->addWidget(cancelB);
    hlayout->addStretch();
    hlayout->addWidget(&info);
    hlayout->addWidget(bar);


    QGridLayout *gl=new QGridLayout(groupB);
    gl->addWidget(listV,0,0,3,1);
    gl->addWidget(addFolder,0,1);
    gl->addWidget(removeFolder,1,1);
    gl->addLayout(hlayout,4,0);
    gl->addWidget(&l,4,1);


//      gl->addWidget(bar,4,1);
//      gl->addWidget(scanB,4,0);
//      gl->addWidget(bar,4,1);


    connect(scanB,SIGNAL(clicked() ),this,SLOT(scan()));
    connect(addFolder,SIGNAL(clicked() ),this,SLOT(addLibraryFolder() ) );
}

void configureContent::scan()
{
    bar->setRange(0,0);
    scanB->setDisabled(true);
    cancelB->setDisabled(false);
    bar->setRange(0,0);
    bar->show();
    l.setText("Starting..");
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
    l.setText("Scanning..");

}

void configureContent::scanDone()
{
    scThread->disconnect();
//      delete scThread;
    scanB->setDisabled(false);
    cancelB->setDisabled(true);

    QString s("Imported %1 files");
    if (scThread->isStoped() )
    {
// 	  bar->setDisabled(true);
        l.setText("Canceled");
    }
    else
    {
        bar->setValue(bar->maximum() );
        l.setText("completed");
    }
    info.setText(s.arg(QString::number( scThread->importedNum() ) ) );
    delete scThread;
}

void configureContent::addLibraryFolder()
{
    QFileDialog *dialog=new QFileDialog(this);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setOption(QFileDialog::ShowDirsOnly);
    dialog->show();
}

