#ifndef LIBRARYIMPORTER_H
#define LIBRARYIMPORTER_H

// #include"database.h"
#include"player.h"
#include <QDirIterator>
#include<QObject>
#include<QMap>
using namespace player;
using namespace player;

class libraryImporter :public QObject
{
    Q_OBJECT
    public:
        libraryImporter();
        ~libraryImporter();
        bool import(const QString path);
	bool importPl(const QString path );
	
        void saveAlbumArt(const QString &s);
        QString error();

        static int n;
	void save();
    private:

        QString albumArt;
        QSqlDatabase database;
        QString name;
        bool isConnected;

        QMap<QString, QString> albumList;
        void createTmpTable();
	QVariant getId(QVariant var,QString table);
	QVariant getAlbumId(QVariant album,QVariant artist);

    signals:
        void error(QString);
};





#endif
