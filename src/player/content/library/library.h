#ifndef LIBRARY_H
#define LIBRARY_H

#include<QPushButton>

#include<QStackedWidget>
#include<KToolBar>
#include<KLineEdit>
#include<KIcon>
#include<core.h>

#include"artistWidget.h"
#include"artistModel.h"
#include"albumTrack.h"
#include<QLinkedList>
class library :public core::abstractContent
{
    Q_OBJECT
    public:
	library(QWidget *parent=0);
	virtual ~library();
	QString name() const;	
	
	QIcon icon() const
	{
	   return KIcon("server-database");
	}
	
    private:

	QListView 	*artistV;
	artistModel  	*artistM;
	albumTrack  	*albumTrV;
	QStackedWidget *stack;

	QAction 		*backAction;
	QAction 		*forwardAction;
	KLineEdit 	*searchLine;


	QLinkedList<tagsEnum> searchTagL;
	
 	core::queryGrt::matchQuery *searchQ;

	//functions
	void inline toolBarInit();
	void activated(const int n);
	
    public slots:
	void artistActivated(const QModelIndex& index);            
	void goToArtist();
	void goToAlbum();
	
	void dbChanged();
	void checkNeedUpdates(audioFiles::audioFile f);
	void search(const QString& text);

    
};

#endif
