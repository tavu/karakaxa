#ifndef LIBRARYIMPORTER_H
#define LIBRARYIMPORTER_H

// #include"database.h"
#include"albumEntry.h"
#include <QDirIterator>
#include<QObject>
#include<QMap>
#include<QSqlDatabase>

class libraryImporter :public QObject
{
    Q_OBJECT
    public:
        libraryImporter();
        ~libraryImporter();
        albumEntry import(const QString &url);
	bool importPl(const QString &path );
	
        void saveAlbumArt(const QString& albumArt, const albumEntry& al);
        QString error();
	
        static int n;
	void save();
    private:

        QString albumArt;
        QSqlDatabase database;
        QString name;
        bool isConnected;

//         QMap<int, QString> albumList;
        void createTmpTable();
	QVariant getId(QVariant var,QString table);
	QVariant getAlbumId(QVariant album,QVariant artist);

    signals:
        void error(QString);
};

#endif
