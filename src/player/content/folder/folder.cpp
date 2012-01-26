#include"folder.h"


#include<QTableView>
#include<KIcon>
#include<KDirModel>
#include<KDirLister>
#include"myFileSystemModel.h"

#include<KFileItemDelegate>
#include<QDebug>
#include<KConfigGroup>

using namespace core;
// #define DIRECTORYM "inode/directory"
folderContent::folderContent(QWidget *parent)
        :abstractContent(parent),playlistM(0)
{
    navigatorModel = new KFilePlacesModel(this);
    navigator = new KUrlNavigator(navigatorModel,KUrl( QDir::home().path() ),this);

    model = new myFileSystemModel(this);
    proxyM=new folderProxyModel(this);
    proxyM->setFilterCaseSensitivity(Qt::CaseInsensitive);
    
    view=new views::treeView(this);
    view->setModel(proxyM);
    view->setDragDropMode(QAbstractItemView::DragDrop);   

    toolBar=new KToolBar(this);
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );

    backAction = new QAction( KIcon( "go-previous" ),"go back", this );
    toolBar->addAction( backAction );
    connect( backAction, SIGNAL( triggered( bool) ), this, SLOT( back() ) );


    forwardAction = new QAction( KIcon( "go-next" ),"go forward", this );
    toolBar->addAction( forwardAction );
    connect( forwardAction, SIGNAL( triggered( bool) ), this, SLOT( forward() ) );

    upAction = new QAction( KIcon( "go-up" ),"go up", this );
    toolBar->addAction( upAction );
    connect( upAction, SIGNAL( triggered( bool) ), this, SLOT( up() ) );
   
    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacer);
    
    searchLine =new KLineEdit(this);
    searchLine->setClearButtonShown(true);
    searchLine->setClickMessage(tr("filter"));
    searchLine->setFixedWidth(300);
    searchLine->setVisible(true);
    toolBar->addWidget(searchLine);
        
    connect(searchLine,SIGNAL(textChanged ( const QString & )  ),proxyM,SLOT(setFilterFixedString(QString) ) );    
    
    QVBoxLayout *layout = new QVBoxLayout();
    
    QFrame *f=new QFrame(this);
    f->setFrameShape(QFrame::HLine);
    layout->addWidget(f);
    layout->addWidget(navigator);
    
    layout->addWidget(view);    

    setLayout(layout);

    connect(view,SIGNAL(clicked ( const QModelIndex) ),this,SLOT(setDir(const QModelIndex) ) );
   
    readSettings();
    
    connect(navigator,SIGNAL(urlChanged (KUrl) ),this,SLOT(showUrl(KUrl) ) );
   
    connect(qApp,SIGNAL(aboutToQuit() ),this,SLOT(writeSettings() ) );
    
    connect(view,SIGNAL(showContextMenu(QModelIndex,QModelIndexList) ),this,SLOT(showContexMenuSlot(QModelIndex, QModelIndexList) ) );
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
    if(proxyM->sourceModel()!=model)
    {
        return ;
    }
    
    Qt::KeyboardModifiers m=QApplication::keyboardModifiers();
    
    if(m & Qt::ShiftModifier || m & Qt::ControlModifier )
    {
        return;
    }
    
    QModelIndex i=proxyM->mapToSource(index);

    KFileItem item = model->itemForIndex(i);
    if (item.isDir() || core::isPlaylist(item.url().toLocalFile() ))
    {
        navigator->setUrl( item.url() );
    }
}

void folderContent::showUrl(KUrl url)
{
    if(proxyM->sourceModel()!=0)
    {
        saveStates();
    }
    if(core::isPlaylist(url.toLocalFile()) )
    {
        //due to a bug the view does not make the hidden columns visible again if we just change the sourceModel on the proxyM
        //we set the model on the view to 0 and then set the proxyM again
        
        playlistM=new playlistModel(this);        
        playlistM->setPlPath(url.toLocalFile());        
        proxyM->setSourceModel(playlistM);
        view->setRatingColumn(RATING);
        view->setNotHide(TITLE);
        view->setModel(0);
        view->setModel(proxyM);
        view->header()->restoreState(playlistMState);
    }
    else
    {
        if(proxyM->sourceModel()!=model )
        {
            view->setNotHide(0);
            view->setRatingColumn(DIRCOLUMN+RATING);
            proxyM->setSourceModel(model);
            view->header()->restoreState(folderModelState);

            if(playlistM!=0)
            {
                delete playlistM;
                playlistM=0;
            }
        }
        
        model->dirLister()->openUrl(url);
    }
    searchLine->clear();
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

void folderContent::loaded()
{
    m=new folderContextMenu(this);
    core::contentHdl->addMenu(m);
}

void folderContent::showContexMenuSlot(QModelIndex index, QModelIndexList list)
{
    if(!index.isValid() )
    {
	 return ;
    }
  
    QUrl u=index.data(URL_ROLE).toUrl();    
    QMenu *menu=new QMenu(this);

    QAction *act=new QAction(KIcon("document-edit"),tr("edit"),this );		
    connect(act,SIGNAL(triggered(bool)),this,SLOT(edit()) );	
    menu->addAction(act);
    
    QString s=index.data(URL_ROLE).toUrl().toLocalFile();
    int tag=model->tag(index);
    if(!isAudio(s) || tag==audioFiles::COUNTER||tag==audioFiles::BITRATE ||tag==LENGTH ||tag<0)
    {
	   act->setEnabled(false);
    }
    else
    {
	   act->setEnabled(true);
    }
    
   
    m->setShow(false);
    QList<QUrl>urls=view->getUrls(list);
    core::contentHdl->contextMenu(menu,KUrl(u),urls );
    
    if(!menu->isEmpty() )
    {
	 menu->exec( QCursor::pos() );
    }
    m->setShow(true);
    
    menu->deleteLater();
}

void folderContent::edit()
{
    view->edit( view->currentIndex() );
}

void folderContent::unloaded()
{
  core::contentHdl->removeMenu(m);
  delete m;  
}

void folderContent::writeSettings()
{
    qDebug()<<"write";

    saveStates();

    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "folderContent" );
    group.writeEntry("dir", QVariant( navigator->url() ) );
    group.writeEntry( "playlistMState", QVariant(playlistMState));
    group.writeEntry( "folderModelState", QVariant(folderModelState));
    group.config()->sync();
}

void folderContent::readSettings()
{    
    KSharedConfigPtr config=core::config->configFile();
    KConfigGroup group( config, "folderContent");
    KUrl url=group.readEntry("dir",KUrl() );
    playlistMState=group.readEntry( "playlistMState", QByteArray() ) ;
    folderModelState=group.readEntry( "folderModelState", QByteArray() );

    if(!url.isEmpty() )
    {
        navigator->setUrl(url );
    }
    showUrl(navigator->url());        
}

void folderContent::saveStates()
{
    if(proxyM->sourceModel()==model )
    {
        folderModelState=view->header()->saveState();
    }
    else if(proxyM->sourceModel()==playlistM)
    {
        playlistMState=view->header()->saveState();
    }
}