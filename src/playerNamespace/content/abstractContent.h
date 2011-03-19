#ifndef ABSTRACTMID_H
#define ABSTRACTMID_H
#include<QWidget>
#include<QTreeWidgetItem>
#include<QMenu>
#include<QAction>
class abstractContent :public QWidget
{
    Q_OBJECT

    public:
	abstractContent(QWidget *parent=0);

	virtual ~abstractContent();
    // 	  virtual const QList<QString> getChildren()=0;

	virtual QString name()const =0;

	virtual void update(const int );

	QTreeWidgetItem* item() const;

	void showMenu(QPoint);
	bool isActive();
    // 	  virtual int childrenNum() const;
    protected:

	QMenu menu;
	void addChild(const QString &s);

    private:
	QTreeWidgetItem *widgetItem;
};

Q_DECLARE_INTERFACE(abstractContent,"abCont");


#endif
