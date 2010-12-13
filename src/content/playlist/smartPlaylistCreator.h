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
#include"smartPlaylistModel.h"
class smartPlaylistCreator :public QDialog
{
    Q_OBJECT
    public:
	smartPlaylistCreator(QWidget *parent=0);
	QString 	name();
	QString 	query();
	QSize   	sizeHint() const;
	QDomElement 	xml();
	
	
	smartPlaylistModelItem* item();
	
    private:

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
