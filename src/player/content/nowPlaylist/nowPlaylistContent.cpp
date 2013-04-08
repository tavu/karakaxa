#include"nowPlaylistContent.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include"contentDelegate.h"
nowPlaylistContent::nowPlaylistContent(QWidget* parent): abstractContent(parent)
{
     view=new nplaylistView(this);
//      view->setHeaderHidden(false);
//      view->setRatingColumn(RATING);
     
//      view->setDragDropMode(QAbstractItemView::InternalMove);
     
     for(int i=1;i<FRAME_NUM;i++)
     {
        view->setColumnHidden(i,true);
     }
     
     view->setItemDelegate(new nowPlaylistDelegate(this) );

     QLabel *textL=new QLabel(this);

     textL->setText(tr("Now Playlist") );
     QFont font=textL->font();
     font.setBold(true);
     font.setPointSize(13);
     textL->setFont(font);
     
     QLabel *iconL=new QLabel(this);
     iconL->setPixmap(icon().pixmap(20,20));
               
     QHBoxLayout *hlayout = new QHBoxLayout();
     hlayout->addWidget(iconL);
     hlayout->addWidget(textL);
     hlayout->addStretch();
     
     
     
     QVBoxLayout *layout = new QVBoxLayout(this);
     
     QFrame *f=new QFrame(this);
     f->setFrameStyle(QFrame::HLine);
     
     layout->addWidget(f);
     layout->addLayout(hlayout);
     layout->addWidget(view);
     
     layout->setContentsMargins(10,0,10,0);
     
      toolBar=new KToolBar(this);      
      toolBar->addAction(views::menus()->sufflePlaylist() );
      toolBar->addAction(views::menus()->clearPlaylist() );
      toolBar->addAction(view->removeAction() );
      toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}
