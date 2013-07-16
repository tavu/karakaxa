#include"tagItemHead.h" 

views::tagItemHead::tagItemHead(QObject *parent)   :tagItem()
{   
    setParent(parent);
    _ts=new tagSelector(this);
}

views::tagItemHead::~tagItemHead()
{
    clear();
    delete _ts;
}


QVariant views::tagItemHead::headerData(int section, Qt::Orientation orientation, int role) const
{
    return standardItem::headerData(section, orientation, role);
}

int views::tagItemHead::nextData() const
{
    if(_tagsL.isEmpty())
    {
        return Basic::INVALID;
    }
    return _tagsL[0];
            
}
