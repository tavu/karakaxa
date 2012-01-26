#ifndef VIEWS_FUNC_H
#define VIEWS_FUNC_H
#include<QString>
#include<QVariant>
#include"decoration/decoration.h"
namespace views
{
    QString 	prettyLength(int l);
    QString     prettyLength(qint64 l);
    QString 	prettySize(int n);
    QVariant	pretyTag(QVariant var,int t);
    QString	    tagName(int t);
    void	    init();
    void 	    cleanUp();
};

#endif