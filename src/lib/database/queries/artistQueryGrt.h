#ifndef ARTISTQUERYGRT_H
#define ARTISTQUERYGRT_H

#include "queryGeneration.h"

namespace database
{

    class artistQueryGrt :public queryGrt
    {
        Q_OBJECT
        public:
            artistQueryGrt(QObject *parent=0) :queryGrt(parent)
            {
            }

            QString queryString() const;

            bool select();
            QStringList result()
            {
                return list;
            }

        private slots:
             virtual void dbEvents(dbEventP e);

        private:
            QStringList list;
    };

    
}

#endif