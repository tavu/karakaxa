#include"abstractContent.h"

abstractContent::abstractContent(QWidget *parent)
        :QWidget(parent)
{
    widgetItem=new QTreeWidgetItem ( );
}


QTreeWidgetItem* abstractContent::item() const
{
    widgetItem->setText(0,name() );
    return widgetItem;
}

void abstractContent::addChild(const QString &s)
{
    QTreeWidgetItem *it=new QTreeWidgetItem(widgetItem);
    it->setText(0,s );
}

void abstractContent::update(const int )
{}

void abstractContent::showMenu(QPoint p)
{
    if (!menu.isEmpty() )
    {
        menu.popup( p);
    }

}
