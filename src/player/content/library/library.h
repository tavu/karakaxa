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

	QWidget *buttonWidget;

	QListView *artistV;
	artistModel  *artistM;
	albumTrack  *albumTrV;
	QStackedWidget *stack;

	QIcon playIcon;

// 	KToolBar *toolBar;
	QAction *backAction;
	QAction *forwardAction;
	KLineEdit *searchLine;

	QPushButton *refresh;

	QLinkedList<tagsEnum> searchTagL;
	
 	core::queryGrt::matchQuery *searchQ;
// 	
	//functions
	void buttonInit();
	void inline toolBarInit();
	void updateQueries(int t);
	void activated(const int n);
	QString searchString;
	
    public slots:
	void artistActivated(const QModelIndex& index);
      
	void artistNeedUpdate(audioFiles::audioFile f);
      
	void toAlbum(const QString &s1,const QString &s2);
	void goToArtist();
	void goToAlbum();
	
	void dbChanged();
    //      private slots:
	void search(const QString& text);
	
//     private slots:
// 	void updateQueriesSlot();	
    
};

#endif
