#ifndef ABSTRACTPLAYLIST_H
#define ABSTRACTPLAYLIST_H
#include<QString>
#include"playlist.h"
/*
    this is an abstract interface for playlists
*/
namespace core
{
  
class filePlaylist :public playlist
{      
    public:
      
        static const int OK=0;
        static const int FILENOTFOUND=1;
        static const int CANTOPENFILE=2;
        static const int UNOWN_ERR=3;


        filePlaylist(QObject *parent=0) :playlist(parent),_saveToRelative(false)
        {            
        }

    public slots:
        virtual void insertUrl(int pos,QString u)=0;
        virtual bool load()=0;
        virtual bool save()=0;
    public:
        virtual QStringList urls() const=0;


        virtual QString path() const=0;


        virtual int  error() const=0;

        bool saveToRelativePath()
        {
            return _saveToRelative;
        }

        void setSaveToRelativePath(bool b)
        {
            _saveToRelative=b;
        }


    protected:
        bool _saveToRelative;
        
    
  protected:
        QString toFullPath(const QString &s) const;
};



core::filePlaylist* getPlaylist(const QString &url);











    
};




#endif