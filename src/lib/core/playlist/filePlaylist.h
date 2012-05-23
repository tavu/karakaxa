#ifndef ABSTRACTPLAYLIST_H
#define ABSTRACTPLAYLIST_H
#include<QString>
#include"playlist.h"
#include<QUrl>
#include<QFile>
#include "../func.h"
/*
    this is an abstract interface for playlists
*/
namespace core
{

class filePlaylist :public playlist
{
    Q_OBJECT
    public:

        static const int OK=0;
        static const int FILENOTFOUND=1;
        static const int CANTOPENFILE=2;
        static const int UNOWN_ERR=3;


        filePlaylist(const QString s,QObject *parent=0)
        :playlist(parent),_saveToRelative(true),_path(s),file(s,this)
        {}

    public slots:

        virtual void insertUrl(int pos,QString u)=0;
//         virtual void insertUrls(int pos,QStringList l)=0;
        virtual bool load()=0;
        virtual bool save()=0;
        virtual bool rename(QString &name)
        {
            file.rename(name);
            err=file.error();
            if(err!=QFile::NoError )
            {
                return false;
            }
            _path=folder(_path)+name;
            file.setFileName(_path);
            return true;
        }
        bool exist()
        {
            return file.exists();
        }
        bool create();

    public:
        virtual QStringList urls() const=0;


        QString path() const
        {
            return _path;
        }

        bool saveToRelativePath()
        {
            return _saveToRelative;
        }

        void setSaveToRelativePath(bool b)
        {
            _saveToRelative=b;
        }

        int error() const
        {
            return err;
        }


    protected:
        //creates a new file and add the default data for every playlist
        //this implementation just create an empty file.
        virtual bool createFile();

        bool _saveToRelative;

        QFile   file;
        QString _path;
        int     err;

    protected:
        QString toFullPath(const QString &s) const;

};



core::filePlaylist* getPlaylist(const QString &url);
// core::filePlaylist* getPlaylist(const QUrl &url)
// {
//     return getPlaylist(url.toLocalFile() );
// }

};




#endif