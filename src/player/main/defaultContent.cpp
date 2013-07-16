#include"defaultContent.h"
#include "nplaylistModel.h"

#include"../content/library/library.h"
#include"../content/folder/folder.h"
// #include"../content/playlist/playlistContent.h"
#include"../content/configure/configureContent.h"
#include"../content/edit/editTrackContent.h"
#include"../content/nowPlaylist/nowPlaylistContent.h"

#include<core/content/contentHandler.h>
void loadDefault()
{
    using namespace core;
      library *l=new library();      
      folderContent *f=new folderContent();
//       playlistContent *pl=new playlistContent();
      configureContent *c=new configureContent();
     nowPlaylistContent *n=new nowPlaylistContent();      
    nplModel *nowPlayListM=new nplModel();
    nowPlayListM->setParent(qApp);
      n->setModel(nowPlayListM);
      
      contentHdl->addContent(l);
      contentHdl->addContent(f);
//       contentHdl->addContent(pl);
      contentHdl->addContent(n);      
      contentHdl->addContent(c);
          
//       contentHdl->addContent(nl);

//       contentHdl->setCurrentContent(l);
      
      editTrackMenu *m=new editTrackMenu();
      contentHdl->addMenu(m);
    contentHdl->setCurrentContent(l);
//        coverDownloaderWidget *w=new coverDownloaderWidget(this);
//        contentHdl->addWidget(w);
}
