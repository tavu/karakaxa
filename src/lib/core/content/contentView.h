#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H
#include "abstractContent.h"
// #include"contentList.h"
#include<QTreeView>
#include<KToolBar>
#include<QStackedWidget>
namespace core
{
    
namespace contentsPrivate
{
    
class contentView :public QObject
{
    Q_OBJECT
    public:
      explicit contentView(QObject* parent = 0);
      ~contentView();
      void setView(QTreeView *v)
      {
        view=v;
        view->setModel(model);
        connect(view,SIGNAL(activated( const QModelIndex & ) ),this, SLOT(activateContFromIndex (const QModelIndex &) ) );
      }
      
      core::abstractContent* contentFromIndex(const QModelIndex &in) const;
      
      QFrame* mainView() const;

	
      KToolBar* toolBar() const
      {
	    return _toolBar;
      }
      
    private:
        QTreeView *view;
        QStandardItemModel *model;
        QStackedWidget *stack;
        KToolBar *_toolBar;
        
	
    public slots:
        void contentActivated(core::abstractContent *content,core::abstractContent *pre);
        void contentAdded(core::abstractContent *content);
        void contentRemoved(core::abstractContent *content);
        
    public slots:
        void activateContFromIndex(const QModelIndex &in);
};//class

extern contentView *contView;  

};//contentsPrivate

};//core
#endif