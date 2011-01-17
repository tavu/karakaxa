#ifndef SONGVIEW_H
#define SONGVIEW_H

#include"../myTreeView.h"
 #include <QLinkedList>
class songView :public myTreeView
{
    Q_OBJECT
    public:
	songView(QWidget *parent=0,QString name=QString("LibraryView"));

    private:
	void contextMenuEvent(QContextMenuEvent *e);
	QMenu *menu;
	QLinkedList<player::starWidget> stars;
	
	inline void createMenu();
	//actions
	QAction *appendAction;
	QAction *editAction;
	QAction *deletAction;
	QAction *editTrAction;	

    private slots:
	void fileEdit();
	void openEditor();	
    
  public slots:
      void play(const QModelIndex index);
};
#endif
