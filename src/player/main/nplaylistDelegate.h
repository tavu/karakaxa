#ifndef NPLDELEGATE_H
#define NPLDELEGATE_H

#include<QStyledItemDelegate>
#include<QLabel>
#include<core.h>
#include<QFrame>
class nplDelegate :public QStyledItemDelegate
{
public:
    nplDelegate(QObject * parent = 0 );
    void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect, QString& text) const;    
    QWidget *createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void setEditorData ( QWidget * editor, const QModelIndex & index ) const;

private:
    void drawDropIndicator(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void drawContent(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

class nplWidget :public QFrame
{
    Q_OBJECT
    public:
	 nplWidget (QWidget *parent,int row);
	 void updateInfo();
	 void setPlaying();

    private:
	   void mouseDoubleClickEvent ( QMouseEvent * event );
	   QLabel iconL;
	   QLabel artistL;
	   QLabel titleL;
	   QLabel trackL;
	   int row;
	   core::nplPointer pointer;
};

#endif
