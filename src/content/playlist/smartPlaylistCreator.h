#ifndef SMARTPLAYLISTCREATOR_H
#define SMARTPLAYLISTCREATOR_H

#include"QTreeWidget"
#include<KToolBar>
#include<QMenu>
#include<smartPlaylistItem.h>
#include<QDialogButtonBox>
#include<QLineEdit>
#include<QLabel>
#include <QDialog>
#include<QDomDocument>
#include"smplaylistItem.h"
class smartPlaylistCreator :public QDialog
{
    Q_OBJECT
    public:
	smartPlaylistCreator(QWidget *parent=0);
	smartPlaylistCreator(smplaylistItem *item,QWidget *parent=0);
	QString 	name();
	QSize   	sizeHint() const;
	QDomElement 	xml();
	
	
	smplaylistItem* item();
	
    private:

	void init();
	
	QDomElement el;
	QLineEdit *lineE;
	QDialogButtonBox *buttons;
	QTreeWidget *treeW;
	KToolBar *toolBar;

	QMenu *addMenu;

	QAction *matchAction;
	QAction *tagAction;
    // 	  QAction *removeAction;
	
    private slots:

	void addMatch();
	void addTag();
	void remove();
	void ok();
	void cancel();

	void addItem(smartPlaylistItem::Type);

    signals:
	void closed(QString,QString) ;

};
#endif
