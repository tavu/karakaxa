#ifndef CONTENTHANDLER_H
#define CONTENTHANDLER_H

#include"abstractContent.h"
#include "abstractMenu.h"
#include<QTreeView>
#include<QModelIndex>
#include<QMenu>

namespace core
{

class abstractContent;

/*
 * ContentHandler provides a set of functions usefull to manage the contents ,the menus and every add-on
 * without concern of the indernal structure of these operations.
 */

class contentHandler :public QObject
{   
    public:

        class genericContent :public abstractContent
        {
            public:
                genericContent(QWidget *parent);
                QString name() const;

            private:
                QWidget *widget;
        };

    Q_OBJECT    
    public:
        contentHandler(QObject *parent=0);
        ~contentHandler();
    
        QWidget* view();
        
        void setView(QTreeView *v);

        void setCurrentContent(abstractContent *c,int submenu=-1);

        void setCurrentContent(const QModelIndex &in);

        core::abstractContent* currentContent();

        void addContent(abstractContent *c,bool activate=false);
        void removeContent(abstractContent *c);

        void removeContent(int pos);

        core::abstractContent* content(int i);

        core::abstractContent* content(const QModelIndex &in);


        void addWidget(QWidget *w,bool activate=true);
        //for menus
        void addMenu(core::abstractMenu* m);


        void removeMenu(core::abstractMenu* m);

        void contextMenu(QMenu* menu, QUrl u,const QList<QUrl> &urls);

        KToolBar* toolBar();

    public slots:
        void clear();
};
  
  extern contentHandler *contentHdl;
}
#endif
