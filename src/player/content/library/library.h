#ifndef LIBRARY_H
#define LIBRARY_H

#include<QPushButton>

#include<QStackedWidget>
#include <QListView>
#include <QLabel>
#include<KToolBar>
#include<KLineEdit>
#include<KIcon>
#include<core.h>

#include<QLinkedList>
#include<queries/matchQuery.h>
#include<delayLineEdit.h>
#include<views/models/treeView.h>
#include <models/libraryModel/tagItemHead.h>
#include<core/standardModel/standardModel.h>
#include "albumView.h"
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
        QStackedWidget *stack;
//         views::treeView *view;
        albumView *view;
        QListView       *artistV;
        QLabel *artistL;
        
        QAction     *backAction;
        QAction     *forwardAction;
        
        views::delayLineEdit   *searchLine;
        
        standardModel *artistM;
        standardModel *albumTrackM;
        views::tagItemHead *albumH;
        views::tagItemHead *artistH;

        QLinkedList<int> searchTagL;

        database::matchQuery *searchQ;

        //functions
        void inline toolBarInit();
        void activated(const int n);
        
        inline bool onArtist();
        inline bool onAlbum();
        
        inline database::abstractQuery* searchQuery();
        
        QString artistName;

    public slots:
        void search(const QString& text);
        void artistActivated(const QModelIndex &index );
        void goToArtist();
        void goToAlbum();
        
        void artistUpdate();
        void albumUpdate();

};

#endif
