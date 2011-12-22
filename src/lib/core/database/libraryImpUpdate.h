#ifndef LIBRARYIMPORTERUPDATE_H
#define LIBRARYIMPORTERUPDATE_H
#include "libraryImporter.h"

namespace core
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
            //TODO add some mutex work
            return  libraryImporter::importToDb(var,v);
        }

        //nothing to save
        void save()
        {}
};

}
#endif 
