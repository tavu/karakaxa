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
class smartPlaylistCreator :public QDialog
{
    Q_OBJECT
    public:
	smartPlaylistCreator(QWidget *parent=0);
	QString name();
	QString query();
	QSize   sizeHint() const;
    private:

	QLineEdit *lineE;
	QDialogButtonBox *buttons;
	QTreeWidget *treeW;
	KToolBar *toolBar;

	QMenu *addMenu;

	QAction *matchAction;
	QAction *tagAction;
    // 	  QAction *removeAction;

	QString _query;
	void closeEvent ( QCloseEvent * event );
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
