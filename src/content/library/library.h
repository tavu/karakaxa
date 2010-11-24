#ifndef LIBRARY_H
#define LIBRARY_H

#include<QPushButton>


#include<player.h>
#include<KToolBar>
#include<KLineEdit>
#include<KIcon>

#include"artistWidget.h"
#include"albumTrack.h"
#include<QLinkedList>
class library :public abstractContent
{
    Q_OBJECT
    public:
	library(QWidget *parent=0);
	QString name() const;
	void update(const int n);

    private:

	QWidget *buttonWidget;

	artistWidget *artistV;
	albumTrack  *albumTrV;
	QStackedWidget *stack;

	QIcon playIcon;

	KToolBar *toolBar;
	QAction *backAction;
	QAction *forwardAction;
	KLineEdit *searchLine;

	QPushButton *refresh;

	QAction *scan;
	QAction *config;
	QLinkedList<tagsEnum> searchTagL;
	
	int needUpdate;
	
	//functions
	void buttonInit();
	void inline toolBarInit();
	void updateQueries(tagsEnum);
	
    public slots:
	void libraryScan();
	void toAlbum(const QString &s1,const QString &s2);
	void goToArtist();
	void goToAlbum();
    //      private slots:
	void search();
	
    private slots:
	void updateQueriesSlot(tagsEnum);
    
};

#endif
