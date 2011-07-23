#ifndef ALBUMDELEGATE_H
#define ALBUMDELEGATE_H
#include <qstyleditemdelegate.h>

class albumDelegate :public QStyledItemDelegate
{
    public:
	albumDelegate(QObject *parent=0);
    
    protected:
	void paint ( QPainter * painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
	void drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, QRect& rect, QString& text) const;
	QWidget* createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;
	void setEditorData(QWidget *editor,const QModelIndex &index) const;
};

class albumEditor :public QWidget
{
    public:
	   albumEditor(QWidget *parent=0) :QWidget(parent)	   
	   {setAutoFillBackground(true);}
	   
	   void setPixmap(const QPixmap &p)
	   {
		  pic=p;
	   }
	   
	   QPixmap pixmap()
	   {
		  return pic;
	   }
	   
	   void setText(const QString &t)
	   {
		  text=t;
	   }
	   
    protected:
	   void paintEvent ( QPaintEvent * event );
	   
    private:
	   QPixmap pic;
	   QString text;
};


#endif