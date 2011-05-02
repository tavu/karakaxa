#include"folder.h"

#include<QTableView>
#include<KIcon>
#include<KDirModel>
#include<KDirLister>
#include"myFileSystemModel.h"

#include<KFileItemDelegate>
// #include"folderProxyModel.h"
#include<QDebug>
#include<KConfigGroup>

using namespace core;
#define DIRECTORYM "inode/directory"
folderContent::folderContent(QWidget *parent)
        :abstractContent(parent)
{
    navigatorModel = new KFilePlacesModel(this);
    navigator = new KUrlNavigator(navigatorModel,KUrl( QDir::home().path() ),this);

    model = new myFileSystemModel(this);

    model->dirLister()->setMimeFilter(core::config->files()<<DIRECTORYM);

    proxyM=new QSortFilterProxyModel(this);
    proxyM->setSourceModel(model);

    view=new views::treeView(this,"Folder view");
    view->setRatingColumn(DIRCOLUMN+RATING);
    view->setModel(proxyM);
//     view->setFrameShape(QFrame::StyledPanel);

//     disconnect(0,0,view,SLOT(updateStarWidget(QModelIndex,int,int)));
    
    

    toolBar=new KToolBar(this);
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );
//     toolBar->setIconDimensions( 16 );

    //add navigation actions
    backAction = new QAction( KIcon( "go-previous" ),"go back", this );
    toolBar->addAction( backAction );
    connect( backAction, SIGNAL( triggered( bool) ), this, SLOT( back() ) );


    forwardAction = new QAction( KIcon( "go-next" ),"go forward", this );
    toolBar->addAction( forwardAction );
    connect( forwardAction, SIGNAL( triggered( bool) ), this, SLOT( forward() ) );

    upAction = new QAction( KIcon( "go-up" ),"go up", this );
    toolBar->addAction( upAction );
    connect( upAction, SIGNAL( triggered( bool) ), this, SLOT( up() ) );

//     KDirLister *dirL=model->dirLister();
//     connect(dirL,SIGNAL(clear() ),this,SLOT(cleanup() ) );
    
//     connect(model,SIGNAL(updated() ),this,SLOT(cleanup() ) );
    
    
    QVBoxLayout *layout = new QVBoxLayout();
    
    QFrame *f=new QFrame(this);
    f->setFrameShape(QFrame::HLine);
    layout->addWidget(f);
    layout->addWidget(navigator);
//     layout->addWidget(toolBar);
            
//     QFrame *f2=new QFrame(this);
//     f2->setFrameShape(QFrame::HLine);
//     layout->addWidget(f2);
    
    layout->addWidget(view);

    setLayout(layout);

    connect(view,SIGNAL(clicked ( const QModelIndex) ),this,SLOT(setDir(const QModelIndex) ) );
   
     readSettings();
    connect(navigator,SIGNAL(urlChanged (KUrl) ),this,SLOT(showUrl(KUrl) ) );
   
//       navigator->setUrl(QDir::homePath());

//      cd(QDir::homePath());

    connect(qApp,SIGNAL(aboutToQuit() ),this,SLOT(writeSettings() ) );
//     readSettings();
}

const QList<QString> folderContent::getChildren()
{
    QList<QString> l;
    return l;
}

QString folderContent::name() const
{
    return QString(tr("Folder") );
}

void folderContent::cleanup()
{
    view->updateStarWidget(QModelIndex(),0,model->rowCount()-1);
}

void folderContent::setDir(const QModelIndex index)
{
  
    Qt::KeyboardModifiers m=QApplication::keyboardModifiers();
    
    if(m & Qt::ShiftModifier || m & Qt::ControlModifier )
    {
	return;
    }
    
    QModelIndex i=proxyM->mapToSource(index);

    KFileItem item = model->itemForIndex(i);
    if (item.isDir())
    {
        navigator->setUrl( item.url() );
    }
}

void folderContent::showUrl(KUrl url)
{
    model->dirLister()->openUrl(url);
}

void folderContent::cd(KUrl url)
{
    navigator->setUrl( url );
}

void folderContent::up()
{
    navigator->goUp();
}

void folderContent::back()
{
    navigator->goBack();
}

void folderContent::forward()
{
    navigator->goForward();
}

void folderContent::writeSettings()
{

    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "folderContent" );  
    group.writeEntry("dir", QVariant( navigator->url() ) );
    group.config()->sync();    
}

void folderContent::readSettings()
{

    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "folderContent" );
    KUrl url=group.readEntry("dir",KUrl() );
      
    if(!url.isEmpty() )
    {
	navigator->setUrl(url );
    }
    showUrl(navigator->url());

}
