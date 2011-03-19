#ifndef CONTENTHANDLER_H
#define CONTENTHANDLER_H

#include"abstractContent.h"
#include <QList>
#include<QTreeWidget>
#include<QStackedWidget>
#include<QMutex>

// #include<QStandardItemModel>
namespace player
{

class contentHandler :public QObject
{
    Q_OBJECT
    public:
	contentHandler();
	void loadDefault();
	void loadPlugins();
	abstractContent* content(const QModelIndex &index) const;

	void removeContent(abstractContent *content);
	bool isActive(QWidget *w);
	void init(QTreeWidget *tree , QStackedWidget *stack);
    private:
	void itemChanger(QModelIndex *item);
	QTreeWidget *tree;
	QStackedWidget *stack;
	QList<abstractContent * > contentList;

	QTreeWidgetItem item;
	QMutex mutex;
	QList<abstractContent*>history;








    class genericContent :public abstractContent
    {
    public:
        genericContent(QWidget *parent);
        QString name() const;

    private:
        QWidget *widget;
    };


public slots:

    void itemChanger(const QModelIndex &);
    void addContent(abstractContent *,bool activate=false);
    void addWidget(QWidget *w,bool activate=true);
// 	  void editTrackCon(QString url);

};

}
#endif
