#include"treeViewHeader.h"

#include<QPainter>
#include<QVBoxLayout>
#include<QLabel>
#include<QFrame>
#include <QCheckBox>
#include<QButtonGroup>
#include"../decoration/decoration.h"
#include<QDebug>

// #define notHid 1+treeV->getHideFirstsColumn()
views::treeViewHeader::treeViewHeader(QWidget *parent)
        :QHeaderView(Qt::Horizontal,parent),
        menu(0),
        notHid(0)
{
//     treeV=parent;
    setMovable(true);

    setStretchLastSection(true);
    setHighlightSections(true);
    setDefaultAlignment(Qt::AlignLeft);
    setMouseTracking(true);
    
    lines=new QLineF[3];
    
    setProperty("highlight",QVariant(-1));        
         
    setStyleSheet("QHeaderView::section {background-color: transparent; }" );
    //setStyleSheet("QHeaderView {background-color: transparent;border: 1px solid #6c6c6c; }" );
    
}

void views::treeViewHeader::createMenu()
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

void views::treeViewHeader::mousePressEvent(QMouseEvent *e)
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

void views::treeViewHeader::hideClickedColumn()
{
    setSectionHidden(columnClicked,true);
//     treeV->setColumnHidden(columnClicked,true);
}

void views::treeViewHeader::selectColumnW()
{
    QFrame *f=new QFrame(this);
    
    int columnNum=model()->columnCount();

    QButtonGroup *Bgroup=new QButtonGroup(f);
    QVBoxLayout *layout = new QVBoxLayout(f);
    Bgroup->setExclusive (false);

    qDebug()<<"COLUMNS "<<columnNum;
    
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

    f->setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint| Qt::WindowCloseButtonHint  );

    f->setAttribute(Qt::WA_DeleteOnClose);
    f->setWindowModality(Qt::WindowModal);
    f->setLayout(layout);
    f->setWindowTitle(tr("Columns"));
    f->move(QCursor::pos ());


    f->show();

}

void views::treeViewHeader::toggleHideColumn(int i)
{
    setSectionHidden(i,!isSectionHidden(i));
}

QSize views::treeViewHeader::sizeHint () const
{
    return QSize(25,25);
}

void views::treeViewHeader::setNotHide(int num)
{
    notHid=num;
}

int views::treeViewHeader::notHide()
{
    return notHid;
}

views::treeViewHeader::~treeViewHeader()
{
  delete lines;
}

void views::treeViewHeader::paintSection( QPainter * painter, const QRect & r, int logicalIndex ) const
{    
    painter->save();
    
    QRect rect(r);
    rect.setWidth(r.width()-2);
    painter->fillRect(rect,QBrush( palette().window().color() ) );
    
    
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
    painter->fillRect(rect,b);            
    QPalette pal=palette();
    QPen pen(pal.window().color() );

    pen.setWidth(2);
    painter->setPen(pen);
    painter->setOpacity(1);

    lines[0].setP1(rect.topLeft());
    lines[0].setP2(rect.topRight());
    lines[1].setP1(rect.bottomLeft());
    lines[1].setP2(rect.bottomRight());
    lines[2].setP1(rect.bottomRight() );
    lines[2].setP2(rect.topRight());

    painter->drawLines(lines,3);
    painter->restore();   

    painter->save();
    QFont f=painter->font();
    f.setBold(true);
    painter->setFont(f);
    QHeaderView::paintSection(painter,rect,logicalIndex);
    painter->restore();
}
/*

void views::treeViewHeader::leaveEvent ( QEvent * event )
{

//   update();
}

void views::treeViewHeader::enterEvent ( QEvent * event )
{
    mouseFlag=true;
}*/