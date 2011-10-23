#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H
#include "abstractContent.h"
#include"contentList.h"
#include<QTreeView>
#include<KToolBar>
#include<QStackedWidget>
namespace core
{
    
class contentView :public QObject
{
    Q_OBJECT
    public:
      explicit contentView(QObject* parent = 0);
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
	
	
    private slots:
	void contentActivated(core::abstractContent *content);
	void contentAdded(core::abstractContent *content);
	void contentRemoved(core::abstractContent *content);
	
    public slots:
	void activateContFromIndex(const QModelIndex &in);
};

extern contentView *contView;  

};

#endif