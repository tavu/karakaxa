#ifndef ABSTRACTMID_H
#define ABSTRACTMID_H
#include<QWidget>
#include<QMenu>
#include<QAction>
#include<KToolBar>
#include<QStandardItem>
#include <QLinkedList>

// #include"contentHandler.h"
// #include "contentHandler.h"

namespace core
{

class contentView;
class contentList;

class abstractContent :public QWidget
{    
    Q_OBJECT
    
//     friend class core::contentHandler;
      friend class core::contentView;
      friend class core::contentList;

    public:
        abstractContent(QWidget *parent=0);

        virtual ~abstractContent();

        //return the visible name of the content
        virtual QString name()const =0;

        //return the icon of the content
        virtual QIcon icon() const;

        void showMenu(const QPoint p);
        bool isActive();

        //this function will load a content to the contentHandler
        void load();
        //this function will unload a content
        void unload();
        bool isLoaded()
        {
            return _isLoaded;
        }

        //return a qvariant to describe the state of the content.
        //if the qvariant is invaled there would be no valid state.
        virtual QVariant state() const
        {
            return QVariant();
        }
		
    // 	  virtual int childrenNum() const;
    protected:

        QMenu menu;
        void addSubmenu(const QString &s,QIcon icon=QIcon() );
        void addSubmenu(const int pos, const QString &s,QIcon icon=QIcon() );
        void removeSubmenu(const int pos);
        KToolBar *toolBar;

        //this function is called after the content have been loaded
        virtual void loaded();
        //this function is called before the content unloads
        virtual void unloaded()
        {}
        //thes function is called after the content have been deactivated.
        virtual void hiden();

        //this function is called after the content have been activated.
        virtual void activated(const int n);

        void saveToHistory();

        private:
        QStandardItem *_item;
        void updateContent(QStandardItem*);
        QLinkedList<QWidget *> widgets;
        QStandardItem* item();
        void unloadContent();
        void loadContent();
        bool _isLoaded;
        QAction *toolBarAction;
};


// Q_DECLARE_INTERFACE(core::abstractContent,"abCont");

};
#endif
