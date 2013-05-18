#ifndef NEW_LIBRARY_H
#define NEW_LIBRARY_H

#include<core.h>
#include<KIcon>
#include <QHBoxLayout>
#include<models/libraryModel/tagItemModel.h>
#include<QDebug>
#include<models/treeView.h>
#include<audioFile.h>
class libraryContent :public core::abstractContent
{
    Q_OBJECT
    public:
        libraryContent(QWidget *parent=0)
		{
 			view=new views::treeView(this);
			view->setUniformRowHeights(false);
// 			view=new QTreeView(this);
			
			QHBoxLayout *l=new QHBoxLayout(this);
			l->addWidget(view);
			model=new views::tagItemModel(this);			
			view->setModel(model);
			view->setRootIsDecorated (true );
			view->setRatingColumn(Basic::RATING);
			
// 			QModelIndex m=model->index(1,0);
// 			qDebug()<<"fetch "<<model->canFetchMore(m);
// 			model->fetchMore(m);
			
			
// 			for(int i=0;i<model->rowCount();i++)
// 			{
// 				view->setFirstColumnSpanned(i,QModelIndex(),true);
// 			}
// 			
// 			qDebug()<<"ROW"<<model->rowCount();
		}
		
        ~libraryContent(){}

        QString name() const
        {
			return QString("new lib");
        }

        QIcon icon() const
        {
            return KIcon("server-database");
        }

    private:

		views::treeView *view;
		views::tagItemModel *model;
		
};

#endif
