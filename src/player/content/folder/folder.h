#ifndef FOLDERCONTENT_h
#define FOLDERCONTENT_h

#include<QFileSystemModel>
#include<QTreeView>
#include<QHeaderView>
#include<QVBoxLayout>
#include<QSortFilterProxyModel>
#include <kfileplacesmodel.h>
#include<KUrlNavigator>

#include<core.h>
#include<views.h>
#include <QToolBar>
#include<QListView>
#include<KToolBar>
#include<KDirModel>
// #include"folderProxyModel.h"
#include"myFileSystemModel.h"
#include<KLineEdit>
// #include <kfileplacesmodel.cpp>
class folderContent :public core::abstractContent
{
    Q_OBJECT
public:
    folderContent(QWidget *parent=0);
    const QList<QString> getChildren();
    
    QString name() const;
    
    QIcon icon() const	
    {
	   return KIcon("folder-sound");
    }


private:
    void loaded();
    void unloaded()
    {
	 core::contentHdl->removeMenu(m);
	 delete m;
    }
  
    core::abstractMenu *m;
    myFileSystemModel *model;
    KDirModel *dirModel;
    QSortFilterProxyModel  *proxyM;

    KFilePlacesModel *navigatorModel;
    views::treeView *view;
//     treeViewHeader *viewHeader;
    KUrlNavigator *navigator;


//     KToolBar *toolBar;
    //actions
    QAction *upAction;
    QAction *backAction;
    QAction *forwardAction;

    KLineEdit *searchLine;

public slots:

    void writeSettings();
    void readSettings();
    void cd(KUrl);
    void up();
    void back();
    void forward();
    void setDir(const QModelIndex index);
    
  private slots:
    void cleanup();
    void showUrl(KUrl);
    

    
};

class folderContextMenu :public core::abstractMenu
{
    Q_OBJECT
    public:
	
	folderContextMenu(folderContent *c)
	  :abstractMenu(), f(c)
	{	    
	     act=new QAction(KIcon("folder"),tr("go to folder"),this);
	     connect(act,SIGNAL(triggered() ),this,SLOT(cd() ) );
	}
	~folderContextMenu()
	{
	    delete act;
	}
	
	virtual bool canShow(QUrl &u ,bool multFiles)
	{
	    this->u=KUrl(u);
	    if(this->u.isLocalFile() )
	    {
		this->u=u;
		return true;
	    }
	    
	    return false;
	}
	
	QAction* action()
	{
	    return act;
	}
    
    private:      
      folderContent *f;
      QAction *act;
      KUrl u;

    private slots:
	void cd()	
	{
	    f->cd(core::folder(u.toLocalFile()) );
	    core::contentHdl->setCurrentContent(f);
	}
	
};








#endif
