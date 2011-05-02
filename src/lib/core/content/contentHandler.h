#ifndef CONTENTHANDLER_H
#define CONTENTHANDLER_H

#include"abstractContent.h"
#include <QList>
#include<QTreeWidget>
#include<QStackedWidget>
#include<QMutex>
#include <QStandardItemModel>
#include<KToolBar>
// class abstractContent;
// #include<QStandardItemModel>
namespace core
{

class contentHandler :public QObject
{
    friend class abstractContent;
    Q_OBJECT    
    public:
	contentHandler();
	~contentHandler();
	void loadPlugins();
	abstractContent* content(const QModelIndex &index) const;
	abstractContent* currentContent() const;
	void setCurrentContent(core::abstractContent* content);

	void removeContent(abstractContent *content);
	bool isActive(QWidget *w);
	
	void setView(QAbstractItemView* v)
	{
	    view=v;
	    view->setModel(model);
	    connect(view,SIGNAL(activated( const QModelIndex & ) ),this, SLOT(itemChanger (const QModelIndex &) ) );
	}
	
	QFrame* contentView() const;

	KToolBar* toolBar()
	{
	    return _toolBar;
	}
	
    private:
	void activateContent(abstractContent*,bool);
	
	QStackedWidget *stack;
	QList<abstractContent * > contentList;
	KToolBar *_toolBar;

	
	QMutex mutex;
	QList<abstractContent*>history;
	QStandardItemModel *model;
	QAbstractItemView *view;

		
    class genericContent :public abstractContent
    {
    public:
        genericContent(QWidget *parent);
        QString name() const;

    private:
        QWidget *widget;
    };
	

  public slots:

    void itemChanger(const QModelIndex &);
    void addContent(abstractContent *,bool activate=false);
    void addWidget(QWidget *w,bool activate=true);



};





    extern contentHandler *contentHdl;

}
#endif
