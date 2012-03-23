#ifndef ALBUMQUERYGRT_H
#define ALBUMQUERYGRT_H
#include "queryGeneration.h"

namespace database
{

    class albumQueryGrt :public queryGrt
    {
        Q_OBJECT
        public:
            albumQueryGrt(QObject *parent=0) :queryGrt(parent)
            {
            }

            QString queryString() const;

            bool select();
            QList<albumEntry> result()
            {
                return list;
            }

            void setArtist(const QString &a)
            {
                artist_=a;
                _needUpdate=true;
            }

            QString artist()
            {
                return artist_;
            }

            QStringList albums()
            {
                QStringList l;
                l.reserve(list.size() );
                foreach(albumEntry a,list)
                {
                    l.append(a.name);
                }
                return l;
            }

        private slots:
            void setNeedUpdate(const audioFiles::audioFile f);

        private:
            QList<albumEntry> list;
            QString artist_;
    };

}

#endif
