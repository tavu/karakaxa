#ifndef LIBRARY_H
#define LIBRARY_H

#include<QPushButton>

#include<QStackedWidget>
#include<KToolBar>
#include<KLineEdit>
#include<KIcon>
#include<core.h>

#include"artistWidget.h"
#include"albumTrack.h"
#include<QLinkedList>
class library :public core::abstractContent
{
    Q_OBJECT
    public:
	library(QWidget *parent=0);
	QString name() const;	

    private:

	QWidget *buttonWidget;

	artistWidget *artistV;
	albumTrack  *albumTrV;
	QStackedWidget *stack;

	QIcon playIcon;

// 	KToolBar *toolBar;
	QAction *backAction;
	QAction *forwardAction;
	KLineEdit *searchLine;

	QPushButton *refresh;

	QAction *scan;
	QAction *config;
	QLinkedList<tagsEnum> searchTagL;
	
	short needUpdate;
	
	//functions
	void buttonInit();
	void inline toolBarInit();
	void updateQueries(int t);
	void activated(const int n);
	
    public slots:
	void libraryScan();
	void toAlbum(const QString &s1,const QString &s2);
	void goToArtist();
	void goToAlbum();
    //      private slots:
	void search();
	
    private slots:
	void updateQueriesSlot();	
    
};

#endif
