#ifndef COVER_DOWNLOADER_WIDGET_H
#define COVER_DOWNLOADER_WIDGET_H

#include<QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include<QLinkedList>

#include<QPushButton>
#include"coverWidget.h"
#include"coverDownloader.h"
#include<QButtonGroup>
#include<QRadioButton>
namespace views
{

class coverDownloaderWidget :public QDialog
{
	Q_OBJECT
	public:
		coverDownloaderWidget(QWidget *parent=0);
		QString album()
		{
			return _album;
		}
		
		void setAlbum(QString s)
		{
			_album=s;
		}
		
	private:
		QString      _album;
		int 		_albumId;
		
		QLabel      *artistT;
		QLabel      *albumT;
		QListWidget *view;
		QLineEdit   *artistL;
		QLineEdit   *albumL;
		
		coverDownloader *dl;
		QLinkedList<views::imageP> imageL;
		
		QPushButton *moreB;
		QPushButton *clearB;
		QPushButton *saveB;
		QPushButton *cancelB;
		QPushButton *folderSelectB;
		QLineEdit   *folderSelectL;
		
		coverWidget *selectedCover;
		QButtonGroup *fileNameButtons;
		QRadioButton *folderRadio;
		QRadioButton *albumRadio;
		QRadioButton *customRadio;
		QLineEdit *nameEdit;

		
		inline QWidget* saveInfoW();
		inline QWidget* imageViewW();		
		
	private slots:
		void newImage(views::imageP);
		void search();
		void clear();
		void nameChanged(QAbstractButton*);
		void changeLocation();
};
	
};

#endif