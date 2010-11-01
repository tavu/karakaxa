#ifndef SMARTPLAYLISTCREATOR_H
#define SMARTPLAYLISTCREATOR_H

#include"QTreeWidget"
#include<KToolBar>
#include<QMenu>
#include<smartPlaylistItem.h>
#include<QDialogButtonBox>
#include<QLineEdit>
#include<QLabel>
class smartPlaylistCreator :public QWidget
{
    Q_OBJECT
public:
    smartPlaylistCreator(QWidget *parent=0);
public:
    QString name();
private:

    QLineEdit *lineE;
    QDialogButtonBox *buttons;
    QTreeWidget *treeW;
    KToolBar *toolBar;

    QMenu *addMenu;

    QAction *matchAction;
    QAction *tagAction;
// 	  QAction *removeAction;

    QString query;
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
