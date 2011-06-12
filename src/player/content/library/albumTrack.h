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
 
class albumTrack :public QWidget
{
    Q_OBJECT

    public:
	albumTrack(QWidget *parent=0);
	void goToArtist(QString &s);
	void updateQueries();
	
	bool needUpdate()
	{
	    return _needUpdate && queryGen->needUpdate();
	}
	
	void setNeedUpdate(bool t)
	{
	    _needUpdate=t;
	}

    private:

	void labelInit();
	void albumVInit();
	void trackVInit();
		
	void readSettings();

	QSplitter *splitter;
	albumModel *albumM;
	standardModel *trackM;
	views::trackModelItem *trmItem;

    //     QString search;

	QString artist;

	albumWidget *albumV;
	views::treeView *trackV;
	
	core::queryGrt *queryGen;
	core::queryGrt::tagQuery *quer;
	core::queryGrt::matchQuery *andQ;
	core::queryGrt::matchQuery *searchQ;
    
//     treeViewDelegate *trackD;


	QLabel *sLabel;
	QLabel *pLabel;    

	QPushButton *leftB;
	QPushButton *rightB;

	QWidget *albumW;
	
	bool _needUpdate;

    

    public slots:
      
	void writeSettings();
      
	void setSearch(core::queryGrt::matchQuery *q)
	{
	    albumM->setSearch(q);
	    searchQ=q;
	    _needUpdate=true;
	}
	
	void showContexMenuSlot(QModelIndex index, QModelIndexList list) ;

    //      private slots:
	void albumActivated(const QModelIndex &n);
	
	void albumsNeedUpdate(audioFiles::audioFile f);
	
	void setNeedUpdateTrue()
	{
	    _needUpdate=true;
	}

};

#endif
