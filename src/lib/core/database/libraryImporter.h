#ifndef LIBRARYIMPORTER_H
#define LIBRARYIMPORTER_H

// #include"database.h"
#include"album.h"
#include <QDirIterator>
#include<QObject>
#include<QMap>
#include<QSqlDatabase>


namespace core
{
class libraryImporter :public QObject
{
    Q_OBJECT
    public:
        libraryImporter(QObject *parent=0);
        ~libraryImporter();

        virtual albumEntry import(const QString &url);

        bool    importPl(const QString &path );
        void    saveAlbumArt(const QString& albumArt, const albumEntry& al);
        virtual void    save()=0;
        QString error();       

    protected:
        QString albumTable;
        QString trackTable;
        QString artistTable;
        QString genreTable;
        QString composerTable;
        QString playlistTable;
        QSqlDatabase database;

        QVariant    getId(QVariant var,QString table);
        QVariant    getAlbumId(QVariant album,QVariant artist);

        virtual albumEntry importToDb(QVariant[],QVariant *);
        

    signals:
        void error(QString);
};

};
#endif
