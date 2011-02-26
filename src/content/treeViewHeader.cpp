#include"treeViewHeader.h"

#include<QProgressBar>
#include<QVBoxLayout>
#include<QLabel>
#include<QFrame>
#include <QCheckBox>
#include<QButtonGroup>
#include<QApplication>

// #define notHid 1+treeV->getHideFirstsColumn()
treeViewHeader::treeViewHeader(QTreeView *parent)
        :QHeaderView(Qt::Horizontal,parent),
        menu(0),
        notHid(0)
{
    treeV=parent;
    setMovable(true);

    setStretchLastSection(true);
    setHighlightSections(true);
    setDefaultAlignment(Qt::AlignLeft);
    setMouseTracking(true);
    
    lines=new QLineF[3];
    
    setProperty("highlight",QVariant(-1));
    setStyleSheet("QHeaderView::section {background-color: transparent;}");
}

void treeViewHeader::createMenu()
{
    hide=new QAction(tr("Hide Column"),this);
    selectColumn=new QAction(tr("Select Columns"),this);

    menu=new QMenu(this);
    menu->addAction(hide);
    menu->addAction(selectColumn);

    if (columnClicked==notHid)
    {
        hide->setDisabled(true);
    }

    connect(hide, SIGNAL(triggered()), this, SLOT( hideClickedColumn() ));
    connect(selectColumn, SIGNAL(triggered()), this, SLOT( selectColumnW() ));
}

void treeViewHeader::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
    {
        columnClicked=logicalIndexAt (e->pos());
        createMenu();

        menu->exec (QCursor::pos());
        delete menu;
        menu=0;
    }
    else
    {
        QHeaderView::mousePressEvent(e);
    }

}



void treeViewHeader::hideClickedColumn()
{
    treeV->setColumnHidden(columnClicked,true);
}

void treeViewHeader::selectColumnW()
{
    QFrame *f=new QFrame(this);
    int columnNum=model()->columnCount();

    QButtonGroup *Bgroup=new QButtonGroup(f);
    QVBoxLayout *layout = new QVBoxLayout(f);
    Bgroup->setExclusive (false);

    QString name;
    for (int i=0;i<columnNum;i++)
    {
        name=model()->headerData(i,Qt::Horizontal).toString();
        QCheckBox *box=new QCheckBox(name,f);

        if (i==notHid )
        {
            box->setDisabled(true);
        }
        box->setChecked(!isSectionHidden(i) );
        Bgroup->addButton (box,i);

        layout->addWidget(box);
    }
    connect(Bgroup, SIGNAL(buttonClicked (int)), this, SLOT( toggleHideColumn(int) ));
//      f->setWindowFlags(Qt::Tool );
    f->setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint| Qt::WindowCloseButtonHint  );

    f->setAttribute(Qt::WA_DeleteOnClose);
    f->setWindowModality(Qt::WindowModal);
    f->setLayout(layout);
    f->setWindowTitle(tr("Columns"));
    f->move(QCursor::pos ());


    f->show();
//      delete f;
}

void treeViewHeader::toggleHideColumn(int i)
{
    treeV->setColumnHidden(i,!isSectionHidden(i) );
}

QSize treeViewHeader::sizeHint () const
{
    return QSize(25,25);
}


// int treeViewHeader::sectionSizeHint(int column)
// {
//      if(column==0)	return 30;
//
//      return 0;
// }

void treeViewHeader::setNotHide(int num)
{
    notHid=num;
}

int treeViewHeader::notHide()
{
    return notHid;
}

treeViewHeader::~treeViewHeader()
{
  delete lines;
}

void treeViewHeader::paintSection( QPainter * painter, const QRect & rect, int logicalIndex ) const
{
//     painter->save();
//     QHeaderView::paintSection(painter,rect,logicalIndex);
//     painter->restore();
//     return ;
  
    QStyleOptionHeader option;    
    option.initFrom(this);
    
    QRect r=rect;
    painter->save();
    
    painter->fillRect(r,QBrush( palette().window().color() ) );
    
    
    QLinearGradient grad(0.5,0.25,0.5,0.45);
    grad.setColorAt( 0.0, palette().base().color() );
    grad.setColorAt( 0.5, palette().highlight().color() );
//     grad.setSpread(QGradient::ReflectSpread);    
    grad.setSpread(QGradient::RepeatSpread);
    
    painter->setOpacity(0.2);
    
    QPoint p = mapFromGlobal(QCursor::pos());    
    if(viewport()->underMouse() )
    {
	if( logicalIndexAt(p)==logicalIndex)
	{
 	    painter->setOpacity(1);
	}
    }
    else if(property("highlight").toInt()==logicalIndex )
    {
 	painter->setOpacity(1);
    }    
    
    QBrush b(grad);    
    painter->fillRect(r,b);            
    QPalette pal= static_cast<QWidget*>(parent())->palette();
    QPen pen(pal.window().color() );

    pen.setWidth(2);
    painter->setPen(pen);
    painter->setOpacity(1);

    lines[0].setP1(r.topLeft());
    lines[0].setP2(r.topRight());
    lines[1].setP1(r.bottomLeft());
    lines[1].setP2(r.bottomRight());
    lines[2].setP1(r.bottomLeft() );
    lines[2].setP2(r.topLeft());

    painter->drawLines(lines,3);
    painter->restore();
    
    r.setX(r.x()+2);

    painter->save();
    QHeaderView::paintSection(painter,rect,logicalIndex);
    painter->restore();
}
/*

void treeViewHeader::leaveEvent ( QEvent * event )
{

//   update();
}

void treeViewHeader::enterEvent ( QEvent * event )
{
    mouseFlag=true;
}*/