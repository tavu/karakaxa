#include"folder.h"


#include<QTableView>
#include<KIcon>
#include<KDirModel>
#include<KDirLister>
#include"myFileSystemModel.h"

#include<KFileItemDelegate>
#include<KConfigGroup>
#include <QDialog>
#include<QDialogButtonBox>
#include<QComboBox>
#include<libraryFolder.h>

using namespace core;
// #define DIRECTORYM "inode/directory"
folderContent::folderContent(QWidget *parent)
        :abstractContent(parent),playlistM(0)
{
    navigatorModel = new KFilePlacesModel(this);
    navigator = new KUrlNavigator(navigatorModel,KUrl( QDir::home().path() ),this);

    model = new myFileSystemModel(this);
    proxyM=0;

    view=new views::treeView(this);
    view->setDragDropMode(QAbstractItemView::DragDrop);

    toolBar=new KToolBar(this);
    toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );

    toolBar->setFixedHeight(25);
    
    folderToolBar=new KToolBar(this);
    folderToolBar->setToolButtonStyle( Qt::ToolButtonIconOnly );    

    backAction = new QAction( KIcon( "go-previous" ),"go back", this );
    toolBar->addAction( backAction );
    connect( backAction, SIGNAL( triggered( bool) ), this, SLOT( back() ) );


    forwardAction = new QAction( KIcon( "go-next" ),"go forward", this );
    toolBar->addAction( forwardAction );
    connect( forwardAction, SIGNAL( triggered( bool) ), this, SLOT( forward() ) );

    upAction = new QAction( KIcon( "go-up" ),"go up", this );
    toolBar->addAction( upAction );
    connect( upAction, SIGNAL( triggered( bool) ), this, SLOT( up() ) );
    
    folderToolBarAction = toolBar->addWidget(folderToolBar);

    QFrame *fr=new QFrame(folderToolBar);
    fr->setFrameStyle(QFrame::VLine|QFrame::Raised);
//     fr->setFrameStyle(QFrame::Raised);
    folderToolBar->addWidget(fr);
    
    newPlAction = new QAction(views::decor->playListIcon(),"create new playlist", this );
    folderToolBar->addAction( newPlAction );
    connect( newPlAction, SIGNAL( triggered( bool) ), this, SLOT( newPl() ) );

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacer);

    searchLine =new KLineEdit(this);
    searchLine->setClearButtonShown(true);
    searchLine->setClickMessage(tr("filter"));
    searchLine->setFixedWidth(300);
    searchLine->setVisible(true);
    toolBar->addWidget(searchLine);



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
    searchLine->clear();
    if(core::isPlaylist(url.toLocalFile()) )
    {
        if(proxyM!=0)
        {
            saveStates();
            delete proxyM;
        }
        goToPl(url);
    }
    else
    {
        if(proxyM ==0 )
        {
            goToFolder(url);
        }
        else if(proxyM->sourceModel()!=model  )
        {
            saveStates();
            delete proxyM;
            goToFolder(url);
        }

        model->dirLister()->openUrl(url);
    }
}

void folderContent::goToFolder(KUrl url)
{
    proxyM=new folderProxyModel(this);
    folderToolBarAction->setVisible(true);
    view->setNotHide(0);
    view->setRatingColumn(DIRCOLUMN+RATING);
    proxyM->setSourceModel(model);
    proxyM->setFilterCaseSensitivity(Qt::CaseInsensitive);

    view->setModel(proxyM);
    view->header()->restoreState(folderModelState);
    view->setSortingEnabled(true);

    searchLine->clear();
    connect(searchLine,SIGNAL(textChanged ( const QString & )  ),proxyM,SLOT(setFilterFixedString(QString) ) );
    if(playlistM!=0)
    {
        delete playlistM;
        playlistM=0;
    }
    
}


void folderContent::goToPl(KUrl url)
{
    view->setSortingEnabled(false);
    folderToolBarAction->setVisible(false);
    playlistM=new views::filePlaylistModel(this);
    
    playlistM->setPlPath(url.toLocalFile());
    proxyM=new folderProxyModel(this);
    proxyM->setSourceModel(playlistM);
    proxyM->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyM->setFilterKeyColumn(-1);

    view->setRatingColumn(RATING);
    view->setNotHide(TITLE);
    view->setModel(proxyM);
    view->header()->restoreState(playlistMState);
    searchLine->clear();
    
    connect(searchLine,SIGNAL(textChanged ( const QString & )  ),proxyM,SLOT(setFilterFixedString(QString) ) );
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

void folderContent::newPl()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("New playlist"));
    KLineEdit *name=new KLineEdit(&dialog);
    QComboBox *box=new QComboBox(&dialog);
    QLabel *label=new QLabel(tr("Create new playlist files"), &dialog);
    QLabel *nameLabel=new QLabel(tr("name:"), &dialog);
    QLabel *dot=new QLabel(".", &dialog);
    QFont font=dot->font();
    font.setBold(true);
    dot->setFont(font);
    QDialogButtonBox* buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    connect(buttons, SIGNAL(accepted()), &dialog, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), &dialog, SLOT(reject()));
    
    QHBoxLayout *vl=new QHBoxLayout();
    vl->addWidget(nameLabel);
    vl->addWidget(name);
    vl->addWidget(dot);
    vl->addWidget(box);
    
    
    QVBoxLayout *l=new QVBoxLayout(&dialog);
    
    l->addWidget(label);
    l->addLayout(vl);
    l->addWidget(buttons);
    box->addItems(core::config->playListFiles() );

    if(dialog.exec()==QDialog::Accepted)
    {
        KUrl u=navigator->locationUrl();
        QString s=name->text();
        s.append(".");
        s.append(box->currentText() );
        u.addPath(s);        
        s=u.toLocalFile();
        
        core::filePlaylist *pl=getPlaylist(s);
        if(pl->exist() )
        {
            core::status->addError(tr("file already exist") );
            return ;
        }
        if(!pl->create() )
        {
            core::status->addError(tr("error creating playlist file") );
        }
        delete pl;
    }

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

    QAction *editA=new QAction(KIcon("document-edit"),tr("edit"),menu );
    QAction *removeA=0;

    QString s=index.data(URL_ROLE).toUrl().toLocalFile();
    int tag=model->tag(index);

    if( !(index.flags() & Qt::ItemIsEditable) || index.data(DISABLE_ROLE).toBool() )
    {
	   editA->setEnabled(false);
    }
    else
    {
	   editA->setEnabled(true);
    }

    if(proxyM->sourceModel()==playlistM)
    {
        removeA=new QAction(KIcon("list-remove"),"remove",menu);
        menu->addAction(removeA);
    }

    menu->addAction(editA);
    m->setShow(false);
    QList<QUrl>urls=view->getUrls(list);
    core::contentHdl->contextMenu(menu,KUrl(u),urls );

    QAction *a=menu->exec( QCursor::pos() );
    if( a==editA )
    {
         view->edit( view->currentIndex() );
    }
    else if(a==removeA && a!=0)
    {
        foreach(QModelIndex in,list)
        {
            QModelIndex index=proxyM->mapToSource(in);
            if(index.column()==view->notHide())
            {
                playlistM->playlist()->remove(index.row() );
            }
        }

        playlistM->save();
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