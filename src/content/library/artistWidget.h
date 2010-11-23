#ifndef ARTISTWIDGET_H
#define ARTISTWIDGET_H

#include<QListView>
#include"artistModel.h"

class artistWidget :public QListView
{
    Q_OBJECT
    public:
	artistWidget(QWidget *parent=0);

    private:
	QString search;
	artistModel *artistM;
	QListView *artistV;

    private slots:
	void artistActivated(const QModelIndex &index);

    public slots:
	void setSearch(const QString &s);
	
	
    signals:
	void toArtist(QString s1,QString s2);

};
#endif
