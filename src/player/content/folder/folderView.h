#ifndef FOLDER_VIEW_H
#define FOLDER_VIEW_H

#include <models/treeView.h>

class folderView :public views::treeView
{
    public:
        folderView(QWidget *parent=0,QString name=QString()) :treeView(parent,name)
        {}
    protected:
        void dropEvent ( QDropEvent * event );
};
#endif
