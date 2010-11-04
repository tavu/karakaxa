#include"treeViewHeader.h"

#include<QProgressBar>
#include<QVBoxLayout>
#include<QLabel>
#include<QFrame>
#include <QCheckBox>
#include<QButtonGroup>

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
}

inline void treeViewHeader::createMenu()
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
}
