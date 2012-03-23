#ifndef LIBRARYIMPORTERUPDATE_H
#define LIBRARYIMPORTERUPDATE_H

#include "libraryImporter.h"

#include<audioFile.h>

namespace database
{
class libraryImpUpdate :public libraryImporter
{
    public:
        libraryImpUpdate(QObject *parent=0)
            :libraryImporter(parent)
        {
            albumTable = QString("albums");
            trackTable = QString("tracks");
            artistTable = QString ("artists");
            genreTable = QString ("genres");
            composerTable = QString("composers");
            playlistTable = QString("playlists");            
        }
        
        albumEntry importToDb(QVariant var[],QVariant *v)
        {
            //TODO do some mutex work
            return  libraryImporter::importToDb(var,v);
        }

        virtual albumEntry import(const QString &url)
        {
            audioFiles::audioFile f(url);

            if(f.inDataBase() )
            {
                return albumEntry();
            }

            return libraryImporter::import(url) ;
        }
        
        //nothing to save
        void save()
        {}
};

}
#endif 
