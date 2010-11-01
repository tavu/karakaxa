#ifndef NPLAYLISTVIEW_H
#define NPLAYLISTVIEW_H

#include<QListView>
#include<QMouseEvent>
class nplaylistView :public QListView
{
    Q_OBJECT
public:

    nplaylistView(QWidget *parent=0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void performDrag();
    Qt::DropActions supportedDropActions () const;
    int sizeHintForColumn(int column) const;
private:
    QPoint startPos;
    QMenu *menu;
    QAction *removeAction;
    QAction *duplicateAction;


    void contextMenuEvent(QContextMenuEvent *e);
    inline void createMenu();
    void keyPressEvent(QKeyEvent *event);

protected:
    void dragEnterEvent ( QDragEnterEvent * event );
public slots:
    void play(const QModelIndex &i);
private slots:
    void remove();
    void duplicate();

};

#endif
