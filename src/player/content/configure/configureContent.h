#ifndef CONFIGURECONTENT_H
#define CONFIGURECONTENT_H
#include<QFileDialog>
#include<QListView>
#include <QStringListModel>
#include<QGroupBox>
#include"scanTread.h"
#include<QLabel>
#include<QProgressBar>
#include <QCheckBox>
#include<QDialogButtonBox>
#include<core.h>
#include<KIcon>
class configureContent :public core::abstractContent
{
    Q_OBJECT
    public:
	configureContent(QWidget *parent=0);
	QString name() const;
		
	QIcon icon() const
	{
	   return KIcon("configure-other");
	}
	
    private:
	QFileDialog 		*fDialog;
	QListView   		*listV;
	QStringListModel	*model;
	QStringList		sList;
	QGroupBox 		*groupB;

	QPushButton 		*scanB;
	QPushButton 		*cancelB;
	QProgressBar 		*bar;
	QLabel			scanInf;
	QLabel			info;
	scanTread 		*scThread;
	QCheckBox			*rememberPl;

	QDialogButtonBox 	*DbButtons;
	QLineEdit			*dbNameL;
	QLineEdit			*dbUserL;
	QLineEdit			*dbPassL;
	
	QLabel 			dbNameS;
	QLabel 			dbUserS;
	QLabel			dbPassS;
	

	void libconfInit();


    private slots:
	void addLibraryFolder();
	void removeLibraryFolder();
	void scanDone();
	void scan();
	void prepare(const int num);
	void DbButtonClicked(QAbstractButton*);
	void rememberPlSlot(int);
};
#endif
