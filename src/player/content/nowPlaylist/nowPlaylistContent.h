#ifndef NOWPLAYLISTCONTENT
#define NOWPLAYLISTCONTENT
#include<core.h>
#include<views.h>
#include"../../main/nplaylistView.h"

class nowPlaylistContent :public core::abstractContent
{
    public:
	nowPlaylistContent(QWidget *parent=0);
	QString name()const
	{
	    return tr("Now playlist");
	}
	
	QIcon icon() const
	{
	    return KIcon("media-playlist-repeat");
	}
	
	void setModel(QAbstractItemModel *m)
	{
	    view->setModel(m);
	  
	    for(int i=1;i<Basic::FRAME_NUM;i++)
	    {
		view->setColumnHidden(i,true);
	    }
	}
	
    private:
	nplaylistView *view;
};

#endif