#include"coverDownloaderWidget.h"
#include<QGridLayout>
#include<QHBoxLayout>

#include<lfmCover.h>
#include <QListWidgetItem>
#include<QIcon>
#include<QDebug>

#include<QSize>
#include<func.h>
#include<QGroupBox>
#include <KIcon>
#include<QSplitter>
#define SIZE QSize(100,100)
#include<QFileDialog>
#include<QFileInfo>
#include<QGridLayout>

views::coverDownloaderWidget::coverDownloaderWidget(QWidget* parent)
:QDialog(parent)
{
	QSplitter *splitter= new QSplitter (Qt::Horizontal,this);
	_album=tr("unknown");
	splitter->addWidget(saveInfoW() );
	splitter->addWidget(imageViewW() );
	
	QHBoxLayout *hl=new QHBoxLayout();
	hl->addWidget(new QLabel(tr("location:"),this));
	folderSelectB=new QPushButton(KIcon("folder"),QString(),this);
	folderSelectL=new QLineEdit(this);
	hl->addWidget(folderSelectB);
	hl->addWidget(folderSelectL);

	saveB=new QPushButton(QObject::tr("save"),this );
	cancelB=new QPushButton(QObject::tr("cancel"),this );
// 	saveB->setFixedWidth(100);
	QHBoxLayout *hl2=new QHBoxLayout();
	hl2->addWidget(saveB);
	hl2->addWidget(cancelB);
	hl2->setAlignment(Qt::AlignLeft);
// 	hl2->setStretch(0,0);
// 	QWidget* spacer = new QWidget(this);
//     spacer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//   	hl2->addWidget(spacer );
	
	QVBoxLayout *layout=new QVBoxLayout(this);
	layout->addWidget(splitter);
	layout->addLayout(hl);
	layout->addLayout(hl2);
	
	dl=new lastFm::lfmCover(this);
	connect(dl,SIGNAL(newImage(views::imageP)),this,SLOT(newImage(views::imageP)) );
	
	connect(artistL,SIGNAL(returnPressed ()),this,SLOT(search()) );
	connect(albumL,SIGNAL(returnPressed ()),this,SLOT(search()) );
	

	connect(moreB,SIGNAL(released () ),dl,SLOT(fetchCovers()));
	connect(clearB,SIGNAL(released () ),this,SLOT(clear()));
	
	connect(folderSelectB,SIGNAL(released()),this,SLOT(changeLocation()) );
}

QWidget* views::coverDownloaderWidget::imageViewW()
{
	QWidget *w=new QWidget(this);
	view=new QListWidget(w);
	view->setViewMode(QListView::IconMode);
	
	view->setIconSize(SIZE);
	
	
	artistL=new QLineEdit(this);
	albumL=new QLineEdit(this);

	artistT=new QLabel(tr("Artist:"));
	albumT=new QLabel(tr("Album:"));
	
	moreB=new QPushButton(QObject::tr("get more"),this );
	clearB=new QPushButton(QObject::tr("clear"),this );
	
	QHBoxLayout *hl=new QHBoxLayout();
	hl->addWidget(moreB);
	hl->addWidget(clearB);
	QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
	hl->addWidget(spacer);
	

	QGridLayout *l=new QGridLayout(w);
	l->addWidget (artistT,0,0);
	l->addWidget (artistL,0,1);
	
	l->addWidget (albumT,1,0);
	l->addWidget (albumL,1,1);
	
	l->addWidget (view,2,0,1,2);
	l->addLayout(hl,3,0,1,2);

	return w;
}


void views::coverDownloaderWidget::newImage(views::imageP pic )
{
	if(pic.isNull() )
	{
		qWarning("received null image");
		return ;
	}
	
	QString title=QString::number(pic->size().height() );
	title+=" x "+QString::number(pic->size().height() );
	QListWidgetItem *item=new QListWidgetItem(title);
	imageL<<pic;
	item->setIcon( QIcon( *(pic.data()) ) );
// 	item->setSizeHint(SIZE);
 	view->addItem(item);
	
	if(!dl->canFetchMore() )
	{
		moreB->setDisabled(true);
	}
}

void views::coverDownloaderWidget::search()
{
	if( artistL->text()!=dl->artist() || albumL->text()!=dl->album() )
	{
		clear();
	}
	dl->setAlbum(albumL->text());
	dl->setArtist(artistL->text());
	dl->fetchCovers();
}


void views::coverDownloaderWidget::clear()
{
	view->clear();
	dl->clear();
	moreB->setDisabled(false);
}

QWidget* views::coverDownloaderWidget::saveInfoW()
{
	QGroupBox *w=new QGroupBox(this);
// 	w->setFrameShape(QFrame::StyledPanel);
	w->setFixedWidth(200);
		
	QVBoxLayout *l =new QVBoxLayout(w);
	selectedCover=new coverWidget(this);
	selectedCover->setSize(100,90);
	
	
	QGroupBox *nameGroup=new QGroupBox(tr("file name"),this);
	QGridLayout  *nameLayout =new QGridLayout (nameGroup);
	
	fileNameButtons=new QButtonGroup(this);
	folderRadio=new QRadioButton("folder.jpg",w);
	albumRadio=new QRadioButton(album()+".jpg",w);
	customRadio=new QRadioButton(w);

	fileNameButtons->addButton(folderRadio);
	fileNameButtons->addButton(albumRadio);
	fileNameButtons->addButton(customRadio);
	
	nameEdit=new QLineEdit(tr("Custom"),this);
	
	nameLayout->addWidget(folderRadio,0,0,1,2);
	nameLayout->addWidget(albumRadio,1,0,1,2);
	nameLayout->addWidget(customRadio,2,0);
 	nameLayout->addWidget(nameEdit,2,1);
	
	l->addWidget(selectedCover);
	l->addWidget(nameGroup);
	QWidget *spacer=new QWidget(w);
	spacer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
	l->addWidget(spacer);
	
	connect(fileNameButtons,SIGNAL(buttonClicked (QAbstractButton*) ),this ,SLOT(nameChanged(QAbstractButton*) ) );
	
	folderRadio->setChecked(true); 
	nameChanged(folderRadio);
	return w;
}

void views::coverDownloaderWidget::nameChanged(QAbstractButton *b )
{
	if(b==customRadio)
	{
		nameEdit->setDisabled(false);
	}
	else
	{
		nameEdit->setDisabled(true);
	}
}

void views::coverDownloaderWidget::changeLocation()
{
	QFileDialog *dialog=new QFileDialog(this);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setOption(QFileDialog::ShowDirsOnly);
    dialog->exec();

    QStringList l=dialog->selectedFiles ();
	QString s=folderSelectL->text() ;
	QFileInfo fi(folderSelectL->text());
	if(fi.exists())
	{
		dialog->setDirectory(folderSelectL->text());
	}
		
    if(!l.isEmpty())
	{
		folderSelectL->setText(l.at(0));
	}
	delete dialog;
}

