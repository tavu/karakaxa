#ifndef ALBUMTRACK_H
#define ALBUMTRACK_H

#include<QWidget>
#include"albumModel.h"
#include"songView.h"
#include"albumWidget.h"
#include<QPushButton>
#include <QLinkedList>
#include<views.h>
#include<core.h>
#include<QSplitter>
#include<QSortFilterProxyModel>
 
class albumTrack :public QWidget
{
    Q_OBJECT

    public:
	albumTrack(QWidget *parent=0);
	void goToArtist(QString &s);
	void updateQueries();
	
	void setAlbumNeedUpdate(bool t)
	{
	    _albumNeedUpdate=t;
	}

	void setTrackNeedUpdate(bool t)
	{
	   _trackNeedUpdate=t;
	}

    private:

	void labelInit();
	void albumVInit();
	void trackVInit();
		
	void readSettings();

	QSplitter *splitter;
	albumModel *albumM;
	standardModel *trackM;
	QSortFilterProxyModel *proxyM;
	views::trackModelItem *trmItem;

	QString artist;

	albumWidget *albumV;
	views::treeView *trackV;
	
	core::filesQueryGrt *queryGen;
// 	core::queryGrt::tagQuery *quer;
	core::queryGrt::matchQuery *andQ;
	core::queryGrt::abstractQuery *searchQ;   


	QLabel *sLabel;
	QLabel *pLabel;    

	QPushButton *leftB;
	QPushButton *rightB;

	QWidget *albumW;
	
	bool _albumNeedUpdate;
	bool _trackNeedUpdate;

    

    public slots:
      
	void writeSettings();
      
	void setSearch(core::queryGrt::abstractQuery *q)
	{
	    if(q->isValid())
	    {
		albumM->setSearch(q->clone());
// 		core::queryGrt::matchQuery *m=new core::queryGrt::matchQuery(andQ);
// 		andQ->append(q);
		searchQ=q->clone();
	    }
	    else
	    {
// 		queryGen->setQuery(0);
		albumM->setSearch(0);
		searchQ=0;
	    }
// 	    _trackNeedUpdate=true;
// 	    _albumNeedUpdate=true;
	}
	
	void checkNeedUpdates();
	void showContexMenuSlot(QModelIndex index, QModelIndexList list) ;
	void albumActivated(const QModelIndex &n);
	
	void trackEdit()
	{
	    trackV->edit( trackV->currentIndex() );
	}
};

#endif
